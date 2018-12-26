#include "player.h"
#include "units/ship.h"

Player::Player() : Controller () {

}

#include <iostream>
void Player::loop(Context *context, Event *event) {
    if(event->getKey(4)) {
        parent->rotateLeft() ;
    } else if(event->getKey(7)) {
        parent->rotateRight();
    }

    ModuleHandler *modules = parent->getModuleHandler();

    std::vector<Module*> *weapons = modules->getModulesByClass("weapon");

    if(weapons) {
        for(Module *module : *weapons) {
            Weapon *weapon = dynamic_cast<Weapon*>(module);
            if(weapon) {
                weapon->setFiring(event->getKey(44));
            }
        }
    }

    Ship *ship = dynamic_cast<Ship*>(parent);
    if(ship == nullptr) std::cout << "error (parent is not Ship): " << typeid (parent).name() << "\n";

    if(event->getKey(26)) {
        ship->accelerateForward();
    }

    if(event->getKey(9)) {
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

void Player::render(Renderer *renderer, Vector offset) {

}
