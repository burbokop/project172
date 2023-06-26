#include "unit.h"

#include "projectile.h"
#include "src/debug.h"
#include "src/messagetype.h"
#include "src/net/common.h"
#include <src/args.h>
#include <src/assettools/assetprovider.h>
#include <src/assettools/loadabletemplate.h>
#include <src/capabilities/capability.h>
#include <src/capabilities/controller.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>
#include <src/capabilities/warestorage.h>
#include <src/context.h>
#include <src/graphics/abstractrenderer.h>

namespace proj172::core {

std::string Unit::info() const
{
    return templateId();
}

void Unit::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    m_selected = context->property("SU").toNumber<e172::Entity::Id>() == entityId();
    for(const auto& cap : m_capabilities) {
        cap->proceed(context, eventHandler);
    }
    proceedPhysics(context->deltaTime());
}

void Unit::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    m_animator.setAngle(rotation());
    m_animator.setPosition(position());
    const auto spriteSize = m_animator.render(renderer);

    if(m_selected) {
        renderer->drawSquareShifted(position(), (m_selectedAnimationTimer.elapsed() / 50) % int(spriteSize.max()), m_selectedColor);
    }

    for(const auto& cap : m_capabilities) {
        cap->render(context, renderer);
    }

    {
        if(const auto controller = capability<Controller>()) {
            if(const auto person =  controller->person()) {
                const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignTop, 12);
                renderer->drawStringShifted("person: " + person->name(), position() + e172::Vector(spriteSize.x() + 16, -spriteSize.y() * 0.5 - 32), 0xA668D5, format);
                renderer->drawStringShifted("modey: " + std::to_string(person->money()), position() + e172::Vector(spriteSize.x() + 16, -spriteSize.y() * 0.5 - 18), 0xA668D5, format);
            }
        }
    }

    {
        double yOffset = 0;
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignBottom, 12);
        for(const auto& c : m_capabilities) {
            auto offset = renderer->drawStringShifted(c->meta().typeName(),
                                                      position()
                                                          + e172::Vector<double>(60,
                                                                                 spriteSize.y() * 0.5
                                                                                     + 8 + yOffset),
                                                      0xffaaff,
                                                      format);
            yOffset += offset.y();
        }
    }

    if(auto storage = capability<WareStorage>()) {
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignBottom, 12);
        double yOffset = 0;
        for(const auto& info : storage->prettyInfo()) {
            auto offset = renderer->drawStringShifted(info,
                                                      position()
                                                          + e172::Vector<double>(0,
                                                                                 spriteSize.y() * 0.5
                                                                                     + 8 + yOffset),
                                                      0xaaffaa,
                                                      format);
            yOffset += offset.y();
        }
    }

    renderer->drawStringShifted(templateId() + ":" + std::to_string(entityId()),
                                position() + e172::Vector<double>(0, -spriteSize.y() * 0.5 - 16),
                                0x00B358,
                                e172::TextFormat::fromFontSize(11));
}

void Unit::writeNet(e172::WriteBuffer &buf)
{
    const auto needSyncSelf = e172::Entity::needSyncNet();
    buf.write<std::uint8_t>(needSyncSelf ? 1 : 0);
    if (needSyncSelf) {
        e172::Entity::writeNet(buf);
    }
    std::vector<e172::ptr<Capability>> capsToSync;
    capsToSync.reserve(m_capabilities.size());
    for (const auto &c : m_capabilities) {
        if (c->needSyncNet()) {
            capsToSync.push_back(c);
        }
    }
    buf.writeDyn(capsToSync.size(), [&capsToSync](std::size_t i, e172::WriteBuffer &buf) {
        buf.write<e172::PackedEntityId>(capsToSync[i]->entityId());
        capsToSync[i]->writeNet(buf);
    });
}

bool Unit::readNet(e172::ReadBuffer &&buf)
{
    const auto &needSyncSelf = buf.read<std::uint8_t>();
    if (!needSyncSelf)
        return false;
    if (*needSyncSelf > 0) {
        if (!e172::Entity::readNet(std::move(buf))) {
            return false;
        }
    }

    return buf
        .readDyn([this](std::size_t i, e172::ReadBuffer &&buf) -> bool {
            const auto capId = buf.read<e172::PackedEntityId>();
            if (!capId)
                return false;

            const auto it = std::find_if(m_capabilities.begin(),
                                         m_capabilities.end(),
                                         [&capId](const e172::ptr<Capability> &cap) {
                                             return cap->entityId() == *capId;
                                         });
            if (it == m_capabilities.end()) {
                (*it)->readNet(std::move(buf));
            } else {
                e172::Debug::warning("Can not sync capability:", *capId, "not found");
            }
            return true;
        })
        .has_value();
}

bool Unit::needSyncNet() const
{
    for (const auto &c : m_capabilities) {
        if (c->needSyncNet()) {
            return true;
        }
    }
    return e172::Entity::needSyncNet();
}

Unit::Unit(e172::FactoryMeta &&meta)
    : e172::Entity(std::move(meta))
{
    m_selectedColor = e172::randomColor(e172::Random::uniq());
    registerInitFunction([this]() {
        m_health = asset<double>("health");
        m_explosiveRadius = asset<double>("explosive");

        m_animator = asset<e172::Animator>("sprite");
        if(!m_animator.isValid()) {
            m_animator = asset<e172::Animator>("animator");
        }

        const auto capabilityTemplates = asset<std::vector<e172::LoadableTemplate>>("capabilities");
        for(const auto& tmpl : capabilityTemplates) {
            addCapability(assetProvider()->createLoadable<Capability>(tmpl).unwrap());
        }
        setMass(asset<double>("mass", 1));
    });
}

void Unit::addCapability(const e172::ptr<Capability> &capability) {
    assert(capability);
    if (capability && capability->setParentUnit(this)) {
        m_capabilities.push_back(capability);
    }
}

void Unit::addCapability(std::unique_ptr<Capability> &&capability)
{
    assert(capability);
    addCapability(capability.release());
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
            context->emitMessage(~MessageType::FloatingMessage,
                                 e172::VariantVector{entityId(), m_health});
        }

        if(m_health < 0) {
            context->emitMessage(~MessageType::SpawnExplosive,
                                 e172::Args(position(), velocity(), m_explosiveRadius));
            if(const auto mh = capability<ModuleHandler>()) {
                const auto modules = mh->modules();
                for(const auto& module : modules) {
                    if(module) {
                        module->animate(e172::Animator::NotRender, e172::Animator::NotRender);
                    }
                }
            }
            context->emitMessage(e172::Context::DestroyEntity, entityId());
        }
    } else {
        if(dynamic_cast<Projectile*>(this) == nullptr) {
            context->emitMessage(~MessageType::FloatingMessage,
                                 e172::VariantVector{entityId(), "no damage"});
        }
    }
}

Unit::~Unit()
{
    for (const auto &c : m_capabilities) {
        c.destroy();
    }
}

} // namespace proj172::core
