#include "player.h"

#include "../messagetype.h"
#include <src/args.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>
#include <src/capabilities/modules/weapon.h>
#include <src/context.h>
#include <src/debug.h>
#include <src/eventhandler.h>
#include <src/units/ship.h>

namespace proj172::core {

const std::map<std::string, e172::Scancode> Player::s_scancode = {
    {"q", e172::ScancodeQ},           {"w", e172::ScancodeW},
    {"e", e172::ScancodeE},           {"r", e172::ScancodeR},
    {"t", e172::ScancodeT},           {"y", e172::ScancodeY},
    {"u", e172::ScancodeU},           {"i", e172::ScancodeI},
    {"o", e172::ScancodeO},           {"p", e172::ScancodeP},
    {"[", e172::ScancodeKpLeftBrace}, {"]", e172::ScancodeKpRightBrace},
    {"a", e172::ScancodeA},           {"s", e172::ScancodeS},
    {"d", e172::ScancodeD},           {"f", e172::ScancodeF},
    {"g", e172::ScancodeG},           {"h", e172::ScancodeH},
    {"j", e172::ScancodeJ},           {"k", e172::ScancodeK},
    {"l", e172::ScancodeL},           {"space", e172::ScancodeSpace},
};

bool Player::personalKey(e172::EventHandler *eventHandler, std::string id)
{
    if (m_personalScancode.find(id) != m_personalScancode.end()) {
        return eventHandler->keyHolded(m_personalScancode[id]);
    }
    return false;
}

Player::Player(e172::FactoryMeta &&meta)
    : Controller(std::move(meta))
{
    registerInitFunction([this]() {
        auto keymap = asset<e172::VariantMap>("keymap");
        for(auto it = keymap.begin(); it != keymap.end(); ++it) {
            if (s_scancode.find(it->second.toString()) != s_scancode.end()) {
                m_personalScancode[it->first] = s_scancode.at(it->second.toString());
            }
        }
    });
}

void Player::scheduleDocking(Id entity) {
    m_dockRequestedQueue.push(entity);
}

bool Player::createDockingSessionWithUnit(e172::Context *context, Id entity) {
    const auto targetUnit = context->entityById<Unit>(entity);
    const auto docker = parentUnit()->capability<Docker>();
    if(docker && targetUnit) {
        if(docker->createDockingSessionWithUnit(context, targetUnit)) {
            return true;
        } else {
            context->emitMessage(~MessageType::FloatingMessage,
                                 e172::Args(parentUnit()->entityId(), "no awailable nodes"));
        }
    }
    return false;
}


void Player::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    if(auto ship = e172::smart_cast<Ship>(parentUnit())) {
        if(personalKey(eventHandler, "left")) {
            ship->maneuverLeft();
        } else if(personalKey(eventHandler, "right")) {
            ship->maneuverRight();
        }

        while (m_dockRequestedQueue.size() > 0) {
            const auto targetUnit = context->entityById<Unit>(m_dockRequestedQueue.front());
            const auto docker = parentUnit()->capability<Docker>();
            if(docker && targetUnit) {
                if(!docker->createDockingSessionWithUnit(context, targetUnit)) {
                    context->emitMessage(~MessageType::FloatingMessage,
                                         e172::Args(parentUnit()->entityId(), "no awailable nodes"));
                }
            }
            m_dockRequestedQueue.pop();
        }

        if(const auto modules = parentUnit()->capability<ModuleHandler>()) {
            const auto weapons = modules->modules<Weapon>();
            for(const auto& module : weapons) {
                if(const auto weapon = e172::smart_cast<Weapon>(module)) {
                    weapon->setFiring(personalKey(eventHandler, "action"));
                }
            }

            if(ship && personalKey(eventHandler, "warp")) {
                if (!m_warpKeyPressed) {
                    m_warpKeyPressed = true;
                    if(!ship->warp()) {
                        if(!ship->prepareWarp()) {
                            if(ship->inWarp()) {
                                if(!ship->abortWarp(context)) {
                                }
                            }
                        }
                    }
                }
            } else {
                m_warpKeyPressed = false;
            }
        }

        if(ship && personalKey(eventHandler, "forward")) {
            ship->thrustForward();
        }

        if(personalKey(eventHandler, "armor")) {
            releaseArmor();
        }
    }

    this->Controller::proceed(context, eventHandler);
}

void Player::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void Player::onHit(e172::Context *context, int) {
    context->emitMessage(~MessageType::BackgroundFlashing, 8);
}

} // namespace proj172::core
