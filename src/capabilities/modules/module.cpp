#include "module.h"

#include <src/units/camera.h>
#include <src/math/math.h>
#include <src/units/unit.h>

namespace proj172::core {

Module::Module(e172::FactoryMeta &&meta)
    : Capability(std::move(meta))
{
    registerInitFunction([this]() {
        m_animator = asset<e172::Animator>("animation");
        m_audioPlayer = asset<e172::AudioPlayer>("audio");
        m_attachOffset = asset<e172::Vector<double>>("offset");

        bool ok;
        double rate = asset<double>("rate", 1, &ok);
        if(ok) {
            if(!e172::Math::cmpf(rate, 0)) {
                m_timer = e172::ElapsedTimer(60000 / rate);
            }
        } else {
            m_timer = e172::ElapsedTimer(asset<double>("interval", 100));
        }
    });
}

void Module::animate(e172::Animator::Mode mode, e172::Animator::Mode def)
{
    m_animator.setDefaultMode(def);
    m_animator.play(mode);

    if (mode == e172::Animator::Loop)
        m_audioPlayer.play();
    else
        m_audioPlayer.stop();
}

void Module::proceed(e172::Context *, e172::EventHandler *) {
    m_audioPlayer.proceed();
}

void Module::render(e172::AbstractRenderer *renderer) {
    m_audioPlayer.setDistance((parentUnit()->position() - renderer->cameraPosition()).module());

    m_animator.setAngle(parentUnit()->rotation());
    e172::Vector local = parentUnit()->position()
                         + e172::Vector<double>::createByAngle(-m_attachOffset.module(),
                                                               parentUnit()->rotation());
    m_animator.setPosition(local);
    m_animator.render(renderer);
}

} // namespace proj172::core
