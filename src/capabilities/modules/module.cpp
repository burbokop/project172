#include "module.h"
#include "units/unit.h"
#include "units/camera.h"

Module::Module() {
}

Module::Module(Loadable *tmp) : Loadable (tmp) {
}

void Module::animate(unsigned mode, unsigned def) {
    animator.setDefaultMode(def);
    animator.play(mode);
    if(mode == Animator::LOOP) audioPlayer.play();
    else audioPlayer.stop();
}

void Module::tick(Context *context, Event *event) {
    this->audioPlayer.tick(context, event);
}

void Module::render(e172::AbstractRenderer *renderer) {
    Camera* cam = renderer->getCamera();
    if(cam) {
        audioPlayer.setVolumeByDistance((parent->getPosition() - cam->getPosition()).module());
    }

    this->animator.setAngle(parent->getAngle());
    e172::Vector local = parent->getPosition() + e172::Vector::createByAngle(-this->attachOffset.module(), parent->getAngle());
    this->animator.setPosition(local);
    this->animator.render(renderer);
}
