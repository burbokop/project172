#include "module.h"
#include "units/unit.h"
#include "units/camera.h"

#include <engine/math/math.h>

Module::Module() {
    registerInitFunction([this](){
        animator = asset<Animator>("animation");
        audioPlayer = asset<AudioPlayer>("audio");
        attachOffset = asset<e172::Vector>("offset");

        bool ok;
        double rate = asset<double>("rate", 1, &ok);
        if(ok) {
            if(!e172::Math::cmpf(rate, 0)) {
                timer = Timer(60000 / rate);
            }
        } else {
            timer = Timer(asset<double>("interval", 100));
        }
    });
}

void Module::animate(unsigned mode, unsigned def) {
    animator.setDefaultMode(def);
    animator.play(mode);
    if(mode == Animator::LOOP) audioPlayer.play();
    else audioPlayer.stop();
}

void Module::tick(Context *context, e172::AbstractEventHandler *eventHandler) {
    this->audioPlayer.tick(context, eventHandler);
}

void Module::render(e172::AbstractRenderer *renderer) {
    audioPlayer.setDistance((parent()->getPosition() - renderer->cameraPosition()).module());

    this->animator.setAngle(parent()->getAngle());
    e172::Vector local = parent()->getPosition() + e172::Vector::createByAngle(-this->attachOffset.module(), parent()->getAngle());
    this->animator.setPosition(local);
    this->animator.render(renderer);
}
