#include "player.h"
#include "units/ship.h"
#include "context.h"
#include "objectregistry.h"
#include "capabilities/modules/weapon.h"


const std::map<std::string, int> Player::scancode = {
    { "q", SDL_SCANCODE_Q },
    { "w", SDL_SCANCODE_W },
    { "e", SDL_SCANCODE_E },
    { "r", SDL_SCANCODE_R },
    { "t", SDL_SCANCODE_T },
    { "y", SDL_SCANCODE_Y },
    { "u", SDL_SCANCODE_U },
    { "i", SDL_SCANCODE_I },
    { "o", SDL_SCANCODE_O },
    { "p", SDL_SCANCODE_P },
    { "[", SDL_SCANCODE_KP_LEFTBRACE },
    { "]", SDL_SCANCODE_KP_RIGHTBRACE },
    { "a", SDL_SCANCODE_A },
    { "s", SDL_SCANCODE_S },
    { "d", SDL_SCANCODE_D },
    { "f", SDL_SCANCODE_F },
    { "g", SDL_SCANCODE_G },
    { "h", SDL_SCANCODE_H },
    { "j", SDL_SCANCODE_J },
    { "k", SDL_SCANCODE_K },
    { "l", SDL_SCANCODE_L },


    { "space", SDL_SCANCODE_SPACE },
};



bool Player::getPersonalKey(Event *event, std::string id) {
    if(personalScancode.find(id) != personalScancode.end()) {
        return event->getKey(personalScancode[id]);
    }
    return false;
}

Player::Player() : Controller(), Loadable() {
    registerInitFunction([this]() {
        auto keymap = asset<e172::VariantMap>("keymap");
        for(auto it = keymap.begin(); it != keymap.end(); ++it) {
            if(Player::scancode.find(it->second.toString()) != Player::scancode.end()) {
                personalScancode[it->first] = Player::scancode.at(it->second.toString());
            }
        }
    });
}

void Player::setArmor(Ship *armor) {
    this->armor = armor;
}

void Player::tick(Context *context, Event *event) {
    EXISTS(parent()) {

    } else {
        std::cout << "ERRROOOORR\n";
    }

    EXISTS(armor) {

    } else {
        std::cout << "ERRROOOORR\n";
    }


    if(getPersonalKey(event, "left")) {
        parent()->rotateLeft() ;
    } else if(getPersonalKey(event, "right")) {
        parent()->rotateRight();
    }

    Ship *ship = dynamic_cast<Ship*>(parent());

    ModuleHandler *modules = parent()->getModuleHandler();
    if(modules) {
        std::vector<Module*> *weapons = modules->getModulesByClass("Weapon");

        if(weapons) {
            for(Module *module : *weapons) {
                Weapon *weapon = dynamic_cast<Weapon*>(module);
                if(weapon) {
                    weapon->setFiring(getPersonalKey(event, "action"));
                }
            }
        }

        if(ship && getPersonalKey(event, "warp")) {
            if(!warpKeyPressed) {
                warpKeyPressed = true;
                if(!ship->warp()) {
                    if(!ship->prepareWarp()) {
                        if(!ship->abortWarp(context)) {
                        }
                    }
                }
            }
        } else {
            warpKeyPressed = false;
        }
    }

    if(ship && getPersonalKey(event, "forward")) {
        ship->accelerateForward();
    }

    if(getPersonalKey(event, "armor")) {
        releaseArmor();
    }

    this->Controller::tick(context, event);
}

void Player::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void Player::onHit(Context *context, int health) {
    UNUSED(health);
    context->addEvent(parent(), Context::BACKGROUND_FLASHING, 8);
}
