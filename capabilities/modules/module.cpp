#include "module.h"
#include "units/unit.h"

Module::Module() {
}

Module::Module(Loadable *tmp) : Loadable (tmp) {
}

void Module::animate(Uint8 mode, Uint8 def) {
    animator.setDefaultMode(def);
    animator.play(mode);
}

void Module::loop(Context *context, Event *event) {

}

#include <iostream>
void Module::render(Renderer *renderer, Vector offset) {
    this->animator.setAngle(parent->getAngle());

    std::cout << "offset LLL: " << this->offset.getDoubleX() << " " << this->offset.getDoubleY() << "\n";
    Vector local = parent->getPosition() + Vector::createByAngle(-this->offset.module(), parent->getAngle());

    this->animator.setPosition(local);
    this->animator.render(renderer, offset);
}
