#include "projectile.h"
#include "unit.h"

#include <src/capabilities/capability.h>
#include <src/capabilities/controller.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>
#include <src/capabilities/warestorage.h>

#include <src/args.h>
#include <src/context.h>

#include <src/graphics/abstractrenderer.h>
#include <src/assettools/assetprovider.h>
#include <src/assettools/loadabletemplate.h>

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
    for(const auto& cap : m_capabilities) {
        cap->proceed(context, eventHandler);
    }
    proceedPhysics(context->deltaTime());
}

void Unit::render(e172::AbstractRenderer *renderer) {
    m_animator.setAngle(rotation());
    m_animator.setPosition(position());
    const auto spriteSize = m_animator.render(renderer);

    if(m_selected) {
        renderer->drawSquareShifted(position(), (m_selectedAnimationTimer.elapsed() / 50) % int(spriteSize.max()), m_selectedColor);
    }

    for(const auto& cap : m_capabilities) {
        cap->render(renderer);
    }

    {
        double yOffset = 0;
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignBottom, 10);
        for(const auto& c : m_capabilities) {
            auto offset = renderer->drawStringShifted(c->className(), position() + e172::Vector(60, spriteSize.y() * 0.5 + 8 + yOffset), 0xffaaff, format);
            yOffset += offset.y();
        }
    }
    if(auto storage = capability<WareStorage>()) {
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignBottom, 10);
        double yOffset = 0;
        for(const auto& info : storage->prettyInfo()) {
            auto offset = renderer->drawStringShifted(info, position() + e172::Vector(0, spriteSize.y() * 0.5 + 8 + yOffset), 0xaaffaa, format);
            yOffset += offset.y();
        }
    }

    renderer->drawStringShifted(std::to_string(entityId()), position() + e172::Vector(0, -spriteSize.y() * 0.5 - 16), 0x00B358, e172::TextFormat::fromFontSize(11));
}

e172::ptr<Person> Unit::ownerPerson() const {
    return m_ownerPerson;
}

void Unit::setOwnerPerson(const e172::ptr<Person> &ownerPerson) {
    m_ownerPerson = ownerPerson;
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

        const auto capabilityTemplates = asset<std::vector<e172::LoadableTemplate>>("capabilities");
        for(const auto& tmpl : capabilityTemplates) {
            addCapability(assetProvider()->createLoadable<Capability>(tmpl));
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

        for(const auto& capability : m_capabilities) {
            if(const auto controller = e172::smart_cast<Controller>(capability)) {
                controller->onHit(context, static_cast<int>(m_health));
            }
        }

        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::VariantVector { entityId(), m_health });
        }

        if(m_health < 0) {
            context->emitMessage(e172::Context::SPAWN_EXPLOSIVE, e172::Args(position(), velocity(), m_explosiveRadius));
            if(const auto mh = capability<ModuleHandler>()) {
                const auto modules = mh->modules();
                for(const auto& module : modules) {
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

