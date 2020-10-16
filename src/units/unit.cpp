#include "projectile.h"
#include "unit.h"

#include <src/capabilities/capability.h>
#include <src/capabilities/controller.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>

#include <src/args.h>
#include <src/context.h>

#include <src/graphics/abstractrenderer.h>

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
    for(const auto cap : m_capabilities) {
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

    for(const auto cap : m_capabilities) {
        cap->render(renderer);
    }
}

Unit::Unit() {
    std::srand(clock());
    m_selectedColor = e172::randomColor();
    registerInitFunction([this]() {
        m_health = asset<double>("health");
        m_explosiveRadius = asset<double>("explosive");

        m_animator = asset<e172::Animator>("sprite");
        if(!m_animator.isValid()) {
            m_animator = asset<e172::Animator>("animator");
        }

        setMass(asset<double>("mass", 1));
    });
}

void Unit::addCapability(const e172::ptr<Capability> &capability) {
    if(capability->setParentUnit(this)) {
        m_capabilities.push_back(capability);
    }
}

void Unit::removeCapability(const e172::ptr<Capability> &capability) {
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

        for(const auto capability : m_capabilities) {
            if(const auto controller = e172::smart_cast<Controller>(capability)) {
                controller->onHit(context, static_cast<int>(m_health));
            }
        }

        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::VariantVector { entityId(), m_health });
        }

        if(m_health < 0) {
            context->emitMessage(e172::Context::SPAWN_EXPLOSIVE, e172::Args(position(), velocity(), m_explosiveRadius));           
            if(const auto mh = moduleHandler()) {
                const auto modules = mh->modules();
                for(const auto module : modules) {
                    if(module) {
                        module->animate(e172::Animator::NotRender, e172::Animator::NotRender);
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

e172::ptr<ModuleHandler> Unit::moduleHandler() const {
    for(const auto& c : m_capabilities) {
        if(const auto mh = e172::smart_cast<ModuleHandler>(c)) {
            return mh;
        }
    }
    return nullptr;
}

e172::ptr<Docker> Unit::docker() const {
    for(const auto& c : m_capabilities) {
        if(const auto docker = e172::smart_cast<Docker>(c)) {
            return docker;
        }
    }
    return nullptr;
}

