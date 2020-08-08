#include "unit.h"
#include "context.h"
#include "projectile.h"
#include "units/station.h"
#include "time/time.h"

#include <engine/math/math.h>

const double Unit::DEFAULT_ROTATION_SPEED = 0.0014 * 1000;
const double Unit::ANGLE_DELTA_MULTIPLIER = 2;

void Unit::setRotationSpeed(double value)
{
    if(value > DEFAULT_ROTATION_SPEED ){
        rotationSpeed = DEFAULT_ROTATION_SPEED ;

    } else {
        rotationSpeed = value;
    }
}

double Unit::getRotationSpeed() {
    return rotationSpeed;
}

Unit::Unit() : Loadable () {
    registerInitFunction([this](){
        health = asset<double>("health");
        explosiveRadius = asset<double>("explosive");

        animator = asset<Animator>("sprite");
        if(!animator.isValid()) {
            animator = asset<Animator>("animator");
        }
    });
}

void Unit::place(e172::Vector pos, double angle) {
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

Docker *Unit::getDocker() {
    for(Capability *cap : capabilities) {
        Docker* docker = dynamic_cast<Docker*>(cap);
        if(docker != nullptr) {
            return  docker;
        }
    }
    return nullptr;
}

void Unit::rotateLeft() {
    angle = e172::Math::constrainAngle(angle - (getRotationSpeed() * Time::getDeltaTime()));
}

void Unit::rotateRight() {
    angle = e172::Math::constrainAngle(angle + (getRotationSpeed() * Time::getDeltaTime()));
}

void Unit::lockAngle(double angle) {
    angleLocked = true;
    dstAngle = e172::Math::constrainAngle(angle);
}


void Unit::rotateToAngle(double angle) {
    angle = e172::Math::constrainAngle(angle);
    const double delta = getRotationSpeed() * Time::getDeltaTime() * ANGLE_DELTA_MULTIPLIER;
    if(angle + delta - getAngle() < 0) {
        if(std::abs(angle - getAngle()) < M_PI) {
            rotateLeft();
        } else {
            rotateRight();
        }
    } else if(angle - delta - getAngle() > 0) {
        if(std::abs(angle - getAngle()) < M_PI) {
            rotateRight();
        } else {
            rotateLeft();
        }
    }
}

bool Unit::isOnAngle(double angle) {
    angle = e172::Math::constrainAngle(angle);
    const double doubleDelta = getRotationSpeed() * Time::getDeltaTime() * ANGLE_DELTA_MULTIPLIER * 2;
    return !(getAngle() > angle + doubleDelta || getAngle() < angle - doubleDelta);
}

void Unit::unlockAngle() {
    angleLocked = false;
}

e172::Vector Unit::getPosition() {
    return pos;
}

e172::Vector Unit::getVelocity() {
    return e172::Vector();
}

double Unit::getAngle() {
    return angle;
}

void Unit::hit(Context* context, int value) {
    if(value != 0) {
        health -= value;

        for(Capability *capability : capabilities) {
            Controller *controller = dynamic_cast<Controller*>(capability);
            if(controller) {
                controller->onHit(context, health);
            }
        }

        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->addEvent(this, Context::FLOATING_MESSAGE, health);
        }

        if(health < 0) {
            context->addEvent(this, Context::SPAWN_EXPLOSIVE, explosiveRadius);
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

void Unit::tick(Context *context, Event *event) {
    const double rotationSpeed = getRotationSpeed();
    if(angleLocked && std::abs(angle - dstAngle) > rotationSpeed * 5) {
        if(angle > dstAngle) angle -= rotationSpeed;
        else angle += rotationSpeed;
    }

    for(Capability *cap : capabilities) {
        cap->tick(context, event);
    }
}

void Unit::render(e172::AbstractRenderer *renderer) {
    renderer->resolution();
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
    return loadableId();
}

std::string Unit::getType() const {
    return typeid (this).name();
}

