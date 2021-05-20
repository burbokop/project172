#include "player.h"
#include <src/units/ship.h>
#include <src/capabilities/modules/weapon.h>
#include <src/capabilities/modulehandler.h>
#include <src/context.h>
#include <src/capabilities/docker.h>
#include <src/args.h>
#include <src/debug.h>

const std::map<std::string, e172::Scancode> Player::scancode = {
    { "q", e172::ScancodeQ },
    { "w", e172::ScancodeW },
    { "e", e172::ScancodeE },
    { "r", e172::ScancodeR },
    { "t", e172::ScancodeT },
    { "y", e172::ScancodeY },
    { "u", e172::ScancodeU },
    { "i", e172::ScancodeI },
    { "o", e172::ScancodeO },
    { "p", e172::ScancodeP },
    { "[", e172::ScancodeKpLeftBrace },
    { "]", e172::ScancodeKpRightBrace },
    { "a", e172::ScancodeA },
    { "s", e172::ScancodeS },
    { "d", e172::ScancodeD },
    { "f", e172::ScancodeF },
    { "g", e172::ScancodeG },
    { "h", e172::ScancodeH },
    { "j", e172::ScancodeJ },
    { "k", e172::ScancodeK },
    { "l", e172::ScancodeL },

    { "space", e172::ScancodeSpace },
};



bool Player::personalKey(e172::AbstractEventHandler *eventHandler, std::string id) {
    if(personalScancode.find(id) != personalScancode.end()) {
        return eventHandler->keyHolded(personalScancode[id]);
    }
    return false;
}

Player::Player() {
    registerInitFunction([this]() {
        auto keymap = asset<e172::VariantMap>("keymap");
        for(auto it = keymap.begin(); it != keymap.end(); ++it) {
            if(Player::scancode.find(it->second.toString()) != Player::scancode.end()) {
                personalScancode[it->first] = Player::scancode.at(it->second.toString());
            }
        }
    });
}

void Player::scheduleDocking(e172::Entity::id_t entity) {
    dockRequestedQueue.push(entity);
}

bool Player::createDockingSessionWithUnit(e172::Context *context, e172::Entity::id_t entity) {
    const auto targetUnit = context->entityById<Unit>(entity);
    const auto docker = parentUnit()->docker();
    if(docker && targetUnit) {
        if(docker->createDockingSessionWithUnit(context, targetUnit)) {
            return true;
        } else {
            context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::Args(parentUnit()->entityId(), "no awailable nodes"));
        }
    }
    return false;
}


void Player::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(auto ship = e172::smart_cast<Ship>(parentUnit())) {
        if(personalKey(eventHandler, "left")) {
            ship->maneuverLeft();
        } else if(personalKey(eventHandler, "right")) {
            ship->maneuverRight();
        }

        while(dockRequestedQueue.size() > 0) {
            const auto targetUnit = context->entityById<Unit>(dockRequestedQueue.front());
            const auto docker = parentUnit()->docker();
            if(docker && targetUnit) {
                if(!docker->createDockingSessionWithUnit(context, targetUnit)) {
                    context->emitMessage(e172::Context::FLOATING_MESSAGE, e172::Args(parentUnit()->entityId(), "no awailable nodes"));
                }
            }
            dockRequestedQueue.pop();
        }

        if(const auto modules = parentUnit()->moduleHandler()) {
            const auto weapons = modules->modulesOfClass("Weapon");
            for(const auto module : weapons) {
                if(const auto weapon = e172::smart_cast<Weapon>(module)) {
                    weapon->setFiring(personalKey(eventHandler, "action"));
                }
            }

            if(ship && personalKey(eventHandler, "warp")) {
                if(!warpKeyPressed) {
                    warpKeyPressed = true;
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
                warpKeyPressed = false;
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
    context->emitMessage(e172::Context::BACKGROUND_FLASHING, 8);
}
