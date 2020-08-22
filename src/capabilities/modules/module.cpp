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
                timer = e172::ElapsedTimer(60000 / rate);
            }
        } else {
            timer = e172::ElapsedTimer(asset<double>("interval", 100));
        }
    });
}
#include <iostream>
void Module::animate(unsigned mode, unsigned def) {
    animator.setDefaultMode(def);
    animator.play(mode);


    std::cout << "validation: " << audioPlayer.beginningSample().isValid() << audioPlayer.loopSample().isValid() << audioPlayer.endingSample().isValid() << "\n";

    if(mode == Animator::Loop) audioPlayer.play();
    else audioPlayer.stop();
}

void Module::proceed(e172::Context *, e172::AbstractEventHandler *) {
    this->audioPlayer.proceed();
}

void Module::render(e172::AbstractRenderer *renderer) {
    audioPlayer.setDistance((parentUnit()->getPosition() - renderer->cameraPosition()).module());

    this->animator.setAngle(parentUnit()->getAngle());
    e172::Vector local = parentUnit()->getPosition() + e172::Vector::createByAngle(-this->attachOffset.module(), parentUnit()->getAngle());
    this->animator.setPosition(local);
    this->animator.render(renderer);
}
