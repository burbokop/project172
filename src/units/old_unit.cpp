#include "old_unit.h"
#include "projectile.h"

#include <math.h>
#include <src/capabilities/controller.h>

#include <src/engine/math/math.h>
#include <src/engine/args.h>
#include <src/engine/context.h>
#include <src/engine/debug.h>
#include <src/engine/graphics/abstractrenderer.h>
#include <src/capabilities/modules/warpdrive.h>
#include <src/capabilities/modulehandler.h>
#include <src/capabilities/docker.h>

const double old_Unit::DEFAULT_ROTATION_SPEED = 0.0014 * 1000;
const double old_Unit::ANGLE_DELTA_MULTIPLIER = 2;

void old_Unit::setRotationSpeed(double value) {
    if(value > DEFAULT_ROTATION_SPEED ){
        rotationSpeed = DEFAULT_ROTATION_SPEED ;

    } else {
        rotationSpeed = value;
    }
}

double old_Unit::getRotationSpeed() {
    return rotationSpeed;
}

old_Unit::old_Unit() : Loadable () {
    std::srand(clock());
    m_selectedColor = rand() % static_cast<uint32_t>(std::pow(2, 24));
    registerInitFunction([this](){
        health = asset<double>("health");
        explosiveRadius = asset<double>("explosive");

        animator = asset<Animator>("sprite");
        if(!animator.isValid()) {
            animator = asset<Animator>("animator");
        }
    });
}

void old_Unit::place(e172::Vector pos, double angle) {
    this->pos = pos;
    m_angle = angle;
}


void old_Unit::addCapability(Capability *capability) {
    if(capability->setParentUnit(this)) {
        capabilities.push_back(capability);
    }
}

void old_Unit::removeCapability(Capability *capability) {
    std::vector<Capability*>::iterator pos = std::find(capabilities.begin(), capabilities.end(), capability);
    if(pos != capabilities.end()) {
        capability->unsetParentUnit();
        capabilities.erase(pos);
    }
}

ModuleHandler *old_Unit::getModuleHandler() {
    for(Capability *cap : capabilities) {
        ModuleHandler* mh = dynamic_cast<ModuleHandler*>(cap);
        if(mh != nullptr) {
            return  mh;
        }
    }
    return nullptr;
}

Docker *old_Unit::getDocker() {
    for(Capability *cap : capabilities) {
        Docker* docker = dynamic_cast<Docker*>(cap);
        if(docker != nullptr) {
            return  docker;
        }
    }
    return nullptr;
}

void old_Unit::rotateLeft(e172::Context *context) {
    m_angle = e172::Math::constrainRadians(m_angle - (getRotationSpeed() * context->deltaTime()));
}

void old_Unit::rotateRight(e172::Context *context) {
    m_angle = e172::Math::constrainRadians(m_angle + (getRotationSpeed() * context->deltaTime()));
}

void old_Unit::lockAngle(double angle) {
    angleLocked = true;
    dstAngle = e172::Math::constrainRadians(angle);
}


void old_Unit::rotateToAngle(e172::Context *context, double angle) {
    angle = e172::Math::constrainRadians(angle);
    const double delta = getRotationSpeed() * context->deltaTime() * ANGLE_DELTA_MULTIPLIER;
    if(angle + delta - m_angle < 0) {
        if(std::abs(angle - m_angle) < M_PI) {
            rotateLeft(context);
        } else {
            rotateRight(context);
        }
    } else if(angle - delta - m_angle > 0) {
        if(std::abs(angle - m_angle) < M_PI) {
            rotateRight(context);
        } else {
            rotateLeft(context);
        }
    }
}

bool old_Unit::isOnAngle(e172::Context *context, double angle) {
    angle = e172::Math::constrainRadians(angle);
    const double doubleDelta = getRotationSpeed() * context->deltaTime() * ANGLE_DELTA_MULTIPLIER * 2;
    return !(m_angle > angle + doubleDelta || m_angle < angle - doubleDelta);
}

void old_Unit::unlockAngle() {
    angleLocked = false;
}

e172::Vector old_Unit::position() {
    return pos;
}

e172::Vector old_Unit::velocity() {
    return e172::Vector();
}

double old_Unit::angle() const {
    return m_angle;
}


void old_Unit::hit(e172::Context* context, int value) {
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
            e172::Debug::print("spawn exposive:", explosiveRadius);
            context->emitMessage(e172::Context::SPAWN_EXPLOSIVE, e172::Args(position(), velocity(), explosiveRadius));
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
            context->emitMessage(e172::Context::DESTROY_ENTITY, entityId());
        }
    } else {
        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::VariantVector { entityId(), "no damage" });
        }
    }
}

void old_Unit::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    const double rotationSpeed = getRotationSpeed();
    if(angleLocked && std::abs(m_angle - dstAngle) > rotationSpeed * 5) {
        if(m_angle > dstAngle) {
            m_angle -= rotationSpeed;
        } else {
            m_angle += rotationSpeed;
        }
    }

    m_selected = context->property("SU").toNumber<e172::Entity::id_t>() == entityId();

    for(Capability *cap : capabilities) {
        cap->proceed(context, eventHandler);
    }
}

void old_Unit::render(e172::AbstractRenderer *renderer) {
    renderer->resolution();
    animator.setAngle(m_angle);
    animator.setPosition(pos);
    animator.render(renderer);

    if(m_selected) {
        renderer->drawSquareShifted(pos, (selectedAnimationTimer.elapsed() / 50) % 24, m_selectedColor);
    }

    for(Capability *cap : capabilities) {
        cap->render(renderer);
    }
}

old_Unit::~old_Unit() {
    for(Capability *cap : capabilities) {
        removeCapability(cap);
    }
}

std::string old_Unit::info() const {
    return loadableId();
}

