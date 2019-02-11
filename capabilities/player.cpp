#include "player.h"
#include "units/ship.h"
#include "context.h"

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
}

Player::Player(Loadable *tmp) : Controller(), Loadable (tmp) {
    Json::Value keymap = root["keymap"];
    for(Json::Value::const_iterator itr = keymap.begin() ; itr != keymap.end() ; itr++ ) {
        std::string key = itr.key().asString();
        std::string value = keymap[key].asString();
        if(Player::scancode.find(value) != Player::scancode.end()) {
            personalScancode[key] = Player::scancode.at(value);
        }
    }
}

void Player::setArmor(Ship *armor) {
    this->armor = armor;
}

#include <iostream>
void Player::loop(Context *context, Event *event) {
    if(getPersonalKey(event, "left")) {
        parent->rotateLeft() ;
    } else if(getPersonalKey(event, "right")) {
        parent->rotateRight();
    }

    Ship *ship = dynamic_cast<Ship*>(parent);
    if(ship == nullptr) std::cout << "error (parent is not Ship): " << typeid (parent).name() << "\n";

    ModuleHandler *modules = parent->getModuleHandler();
    if(modules) {
        std::vector<Module*> *weapons = modules->getModulesByClass("weapon");

        if(weapons) {
            for(Module *module : *weapons) {
                Weapon *weapon = dynamic_cast<Weapon*>(module);
                if(weapon) {
                    weapon->setFiring(getPersonalKey(event, "action"));
                }
            }
        }

        if(getPersonalKey(event, "warp")) {
            if(!warpKeyPressed) {
                warpKeyPressed = true;
                if(!ship->warp()) {
                    if(!ship->prepareWarp()) {
                        if(!ship->abortWarp()) {
                        }
                    }
                }
            }
        } else {
            warpKeyPressed = false;
        }
    }

    if(getPersonalKey(event, "forward")) {
        ship->accelerateForward();
    }

    if(getPersonalKey(event, "armor")) {
        releaseArmor();
    }

    this->Controller::loop(context, event);
}

void Player::render(Renderer *renderer) {

}

void Player::onHit(Context *context, int health) {
    context->addEvent(nullptr, Context::BACKGROUND_FLASHING, 8);
}
