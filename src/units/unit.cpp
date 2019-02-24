#include "unit.h"
#include "context.h"
#include "projectile.h"

const double Unit::DEFAULT_ROTATION_SPEED = 0.02;

double Unit::getRotationSpeed() {
    return DEFAULT_ROTATION_SPEED;
}

Unit::Unit() : Loadable () {
}

Unit::Unit(Loadable *tmp) {
    tmp->clone(this);
}

void Unit::place(Vector pos, double angle) {
    this->pos = pos;
    this->angle = angle;
}


void Unit::addCapability(Capability *capability) {
    if(capability->setParent(this)) {
        capabilities.push_back(capability);
    }
}

void Unit::removeCapability(Capability *capability) {
    std::vector<Capability*>::iterator pos = std::find(capabilities.begin(), capabilities.end(), capability);
    if(pos != capabilities.end()) {
        capability->unsetParent();
        capabilities.erase(pos);
    }
}

ModuleHandler *Unit::getModuleHandler() {
    for(Capability *cap : capabilities) {
        ModuleHandler* mh = dynamic_cast<ModuleHandler*>(cap);
        if(mh != nullptr) {
            return  mh;
        }
    }
    return nullptr;
}

void Unit::rotateLeft() {
    angle -= getRotationSpeed();
}

void Unit::rotateRight() {
    angle += getRotationSpeed();
}

void Unit::lockAngle(double angle) {
    angleLocked = true;
    dstAngle = angle;
}

void Unit::unlockAngle() {
    angleLocked = false;
}

Vector Unit::getPosition() {
    return pos;
}

double Unit::getAngle() {
    return angle;
}

#include <iostream>
void Unit::hit(Context* context, int value) {
    if(value != 0) {
        Json::Value health = root["health"];
        Json::Value maxHealth = root["health-max"];
        if(maxHealth.isNull()) root["health-max"] = health.asInt();
        root["health"] = health.asInt() - value;

        for(Capability *capability : capabilities) {
            Controller *controller = dynamic_cast<Controller*>(capability);
            if(controller) {
                controller->onHit(context, root["health"].asInt());
            }
        }

        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->addEvent(this, Context::FLOATING_MESSAGE, root["health"].asInt());
        }

        if(root["health"].asInt() < 0) {
            Json::Value explosive = root["explosive"];
            if(explosive.isNumeric()) {
                context->addEvent(this, Context::SPAWN_EXPLOSIVE, explosive.asDouble());
            }
            audioPlayer.stop();
            ModuleHandler *mh = getModuleHandler();
            if(mh) {
                std::vector<Module*> *modules = mh->getAllModules();
                if(modules) {
                    for(Module* module : *modules) {
                        if(module) {
                            module->animate(Animator::NOTRENDER, Animator::NOTRENDER);
                        }
                    }
                }
            }
            context->addEvent(this, Context::DELETE_UNIT);
        }
    } else {
        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->addEvent(this, Context::FLOATING_MESSAGE, const_cast<char*>("no damage"));
        }
    }
}

void Unit::loop(Context *context, Event *event) {
    const double rotationSpeed = getRotationSpeed();
    if(angleLocked && std::abs(angle - dstAngle) > rotationSpeed * 5) {
        if(angle > dstAngle) angle -= rotationSpeed;
        else angle += rotationSpeed;
    }

    for(Capability *cap : capabilities) {
        cap->loop(context, event);
    }
}

void Unit::render(Renderer *renderer) {
    animator.setAngle(angle);
    animator.setPosition(pos);
    animator.render(renderer);
    for(Capability *cap : capabilities) {
        cap->render(renderer);
    }
}

Unit::~Unit() {
    for(Capability *cap : capabilities) {
        removeCapability(cap);
    }
}

std::string Unit::getInfo() {
    return root.get("key", "nuknown").asString();
}

std::string Unit::getType() const {
    return typeid (this).name();
}
