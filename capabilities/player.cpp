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


    for(Module *module : *weapons) {
        Weapon *weapon = dynamic_cast<Weapon*>(module);
        if(weapon) {
            weapon->setFiring(event->getKey(44));
        }
    }



/*
    const weapon = this.parent.moduleHandler.getFreeType('weapon');
    const engine = this.parent.moduleHandler.getFreeType('engine');

    if(weapon) {
        weapon.fire = api.oh.event.code(44);
    }



    */


    Movable *obj = dynamic_cast<Movable*>(parent);
    if(obj == nullptr) std::cout << "error (parent is not Movable): " << typeid (parent).name() << "\n";


    //if(typeid (parent) == typeid (Movable)) {
    //if(engine) {
        if(event->getKey(26)) {
            if(!forwardKeyPressed) {
                forwardKeyPressed = true;
                //this.parent.audioPlayer.play(engine, 24);
                //if(engine.animation !== undefined) engine.animation.play('loop');
            }
            dynamic_cast<Movable*>(parent)->accelerateForward();
        } else {
            if(forwardKeyPressed) {
                forwardKeyPressed = false;
                //this.parent.audioPlayer.stop(engine);
                //if(engine.animation !== undefined) engine.animation.stop();
            }
            dynamic_cast<Movable*>(parent)->accelerateIdle();
        }
    //}
    //}
}

void Player::render(Renderer *renderer, Vector offset) {

}
