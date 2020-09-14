#include "module.h"


#include <src/units/camera.h>
#include <src/engine/math/math.h>

Module::Module() {
    registerInitFunction([this](){
        animator = asset<Animator>("animation");
        audioPlayer = asset<AudioPlayer>("audio");
        attachOffset = asset<e172::Vector>("offset");

        bool ok;
        double rate = asset<double>("rate", 1, &ok);
        if(ok) {
            if(!e172::Math::cmpf(rate, 0)) {
                timer = e172::ElapsedTimer(60000 / rate);
            }
        } else {
            timer = e172::ElapsedTimer(asset<double>("interval", 100));
        }
    });
}

void Module::animate(unsigned mode, unsigned def) {
    animator.setDefaultMode(def);
    animator.play(mode);

    if(mode == Animator::Loop) audioPlayer.play();
    else audioPlayer.stop();
}

void Module::proceed(e172::Context *, e172::AbstractEventHandler *) {
    this->audioPlayer.proceed();
}

void Module::render(e172::AbstractRenderer *renderer) {
    audioPlayer.setDistance((parentUnit()->position() - renderer->cameraPosition()).module());

    this->animator.setAngle(parentUnit()->rotation());
    e172::Vector local = parentUnit()->position() + e172::Vector::createByAngle(-this->attachOffset.module(), parentUnit()->rotation());
    this->animator.setPosition(local);
    this->animator.render(renderer);
}
