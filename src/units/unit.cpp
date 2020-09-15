#include "projectile.h"
#include "unit.h"

#include <src/capabilities/capability.h>
#include <src/capabilities/controller.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>

#include <src/engine/args.h>
#include <src/engine/context.h>

#include <src/engine/graphics/abstractrenderer.h>

bool Unit::selected() const {
    return m_selected;
}

double Unit::health() const {
    return m_health;
}

std::string Unit::info() const {
    return loadableId();
}

void Unit::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    m_selected = context->property("SU").toNumber<e172::Entity::id_t>() == entityId();

    for(Capability *cap : m_capabilities) {
        cap->proceed(context, eventHandler);
    }

    proceedPhysics(context->deltaTime());
}

void Unit::render(e172::AbstractRenderer *renderer) {
    renderer->resolution();
    m_animator.setAngle(rotation());
    m_animator.setPosition(position());
    m_animator.render(renderer);

    if(m_selected) {
        renderer->drawSquareShifted(position(), (m_selectedAnimationTimer.elapsed() / 50) % 24, m_selectedColor);
    }

    for(Capability *cap : m_capabilities) {
        cap->render(renderer);
    }
}

Unit::Unit() {
    std::srand(clock());
    m_selectedColor = e172::randomColor();
    registerInitFunction([this]() {
        m_health = asset<double>("health");
        m_explosiveRadius = asset<double>("explosive");

        m_animator = asset<Animator>("sprite");
        if(!m_animator.isValid()) {
            m_animator = asset<Animator>("animator");
        }

        setMass(asset<double>("mass", 1));
    });
}

void Unit::addCapability(Capability *capability) {
    if(capability->setParentUnit(this)) {
        m_capabilities.push_back(capability);
    }
}

void Unit::removeCapability(Capability *capability) {
    const auto it = std::find(m_capabilities.begin(), m_capabilities.end(), capability);
    if(it != m_capabilities.end()) {
        if(capability->setParentUnit(nullptr)) {
            m_capabilities.erase(it);
        }
    }
}

void Unit::hit(e172::Context *context, int value) {
    if(value != 0) {
        m_health -= value;

        for(Capability *capability : m_capabilities) {
            Controller *controller = dynamic_cast<Controller*>(capability);
            if(controller) {
                controller->onHit(context, static_cast<int>(m_health));
            }
        }

        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::VariantVector { entityId(), m_health });
        }

        if(m_health < 0) {
            context->emitMessage(e172::Context::SPAWN_EXPLOSIVE, e172::Args(position(), velocity(), m_explosiveRadius));
            ModuleHandler *mh = moduleHandler();
            if(mh) {
                const auto modules = mh->modules();
                for(Module* module : modules) {
                    if(module) {
                        module->animate(Animator::NotRender, Animator::NotRender);
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

ModuleHandler *Unit::moduleHandler() const {
    for(const auto& c : m_capabilities) {
        ModuleHandler* mh = dynamic_cast<ModuleHandler*>(c);
        if(mh != nullptr) {
            return  mh;
        }
    }
    return nullptr;
}

Docker *Unit::docker() const {
    for(const auto& c : m_capabilities) {
        Docker* docker = dynamic_cast<Docker*>(c);
        if(docker != nullptr) {
            return  docker;
        }
    }
    return nullptr;
}

