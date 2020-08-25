#include "unit.h"
#include "projectile.h"

#include <math.h>
#include <src/capabilities/controller.h>

#include <src/engine/math/math.h>
#include <src/engine/context.h>
#include <src/engine/graphics/abstractrenderer.h>

const double Unit::DEFAULT_ROTATION_SPEED = 0.0014 * 1000;
const double Unit::ANGLE_DELTA_MULTIPLIER = 2;

void Unit::setRotationSpeed(double value) {
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
    if(capability->setParentUnit(this)) {
        capabilities.push_back(capability);
    }
}

void Unit::removeCapability(Capability *capability) {
    std::vector<Capability*>::iterator pos = std::find(capabilities.begin(), capabilities.end(), capability);
    if(pos != capabilities.end()) {
        capability->unsetParentUnit();
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

void Unit::rotateLeft(e172::Context *context) {
    angle = e172::Math::constrainAngle(angle - (getRotationSpeed() * context->deltaTime()));
}

void Unit::rotateRight(e172::Context *context) {
    angle = e172::Math::constrainAngle(angle + (getRotationSpeed() * context->deltaTime()));
}

void Unit::lockAngle(double angle) {
    angleLocked = true;
    dstAngle = e172::Math::constrainAngle(angle);
}


void Unit::rotateToAngle(e172::Context *context, double angle) {
    angle = e172::Math::constrainAngle(angle);
    const double delta = getRotationSpeed() * context->deltaTime() * ANGLE_DELTA_MULTIPLIER;
    if(angle + delta - getAngle() < 0) {
        if(std::abs(angle - getAngle()) < M_PI) {
            rotateLeft(context);
        } else {
            rotateRight(context);
        }
    } else if(angle - delta - getAngle() > 0) {
        if(std::abs(angle - getAngle()) < M_PI) {
            rotateRight(context);
        } else {
            rotateLeft(context);
        }
    }
}

bool Unit::isOnAngle(e172::Context *context, double angle) {
    angle = e172::Math::constrainAngle(angle);
    const double doubleDelta = getRotationSpeed() * context->deltaTime() * ANGLE_DELTA_MULTIPLIER * 2;
    return !(getAngle() > angle + doubleDelta || getAngle() < angle - doubleDelta);
}

void Unit::unlockAngle() {
    angleLocked = false;
}

e172::Vector Unit::position() {
    return pos;
}

e172::Vector Unit::velocity() {
    return e172::Vector();
}

double Unit::getAngle() {
    return angle;
}


void Unit::hit(e172::Context* context, int value) {
    if(value != 0) {
        health -= value;

        for(Capability *capability : capabilities) {
            Controller *controller = dynamic_cast<Controller*>(capability);
            if(controller) {
                controller->onHit(context, static_cast<int>(health));
            }
        }

        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::VariantVector { entityId(), health });
        }

        if(health < 0) {
            context->emitMessage(e172::Context::SPAWN_EXPLOSIVE, e172::VariantVector { position(), velocity(), explosiveRadius });
            ModuleHandler *mh = getModuleHandler();
            if(mh) {
                std::vector<Module*> *modules = mh->getAllModules();
                if(modules) {
                    for(Module* module : *modules) {
                        if(module) {
                            module->animate(Animator::NotRender, Animator::NotRender);
                        }
                    }
                }
            }
            context->emitMessage(e172::Context::DELETE_UNIT, entityId());
        }
    } else {
        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::VariantVector { entityId(), "no damage" });
        }
    }
}

void Unit::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    const double rotationSpeed = getRotationSpeed();
    if(angleLocked && std::abs(angle - dstAngle) > rotationSpeed * 5) {
        if(angle > dstAngle) angle -= rotationSpeed;
        else angle += rotationSpeed;
    }

    for(Capability *cap : capabilities) {
        cap->proceed(context, eventHandler);
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

