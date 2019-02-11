#include "module.h"
#include "units/unit.h"

Module::Module() {
}

Module::Module(Loadable *tmp) : Loadable (tmp) {
}

void Module::animate(Uint8 mode, Uint8 def) {
    animator.setDefaultMode(def);
    animator.play(mode);

    if(mode == 1) audioPlayer.play();
    else audioPlayer.stop();
}

void Module::loop(Context *context, Event *event) {
    this->audioPlayer.loop(context, event);
}

void Module::render(Renderer *renderer) {
    this->animator.setAngle(parent->getAngle());
    Vector local = parent->getPosition() + Vector::createByAngle(-this->attachOffset.module(), parent->getAngle());
    this->animator.setPosition(local);
    this->animator.render(renderer);
}
