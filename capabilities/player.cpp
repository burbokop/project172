#include "player.h"
#include "units/movable.h"

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

    Movable *obj = dynamic_cast<Movable*>(parent);
    if(obj == nullptr) std::cout << "error (parent is not Movable): " << typeid (parent).name() << "\n";

    if(event->getKey(26)) {
        if(dynamic_cast<Movable*>(parent)->accelerateForward() && !forwardKeyPressed) {
            forwardKeyPressed = true;
            //this.parent.audioPlayer.play(engine, 24);
            //if(engine.animation !== undefined) engine.animation.play('loop');
        }
    } else {
        if(forwardKeyPressed) {
            forwardKeyPressed = false;
            //this.parent.audioPlayer.stop(engine);
            //if(engine.animation !== undefined) engine.animation.stop();
        }
    }
}

void Player::render(Renderer *renderer, Vector offset) {

}
