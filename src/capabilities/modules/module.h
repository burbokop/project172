#pragma once

#include "../capability.h"
#include <src/iinformative.h>
#include <src/utility/animator.h>
#include <src/audio/audioplayer.h>

namespace proj172::core {

class Module : public Capability, public Informative
{
public:
    Module(e172::FactoryMeta &&meta);
    void animate(e172::Animator::Mode mode, e172::Animator::Mode def = e172::Animator::Inactive);

    // Entity interface
public:
    void proceed(e172::Context *, e172::EventHandler *);
    void render(e172::Context *context, e172::AbstractRenderer *renderer);

protected:
    e172::Animator m_animator;
    e172::AudioPlayer m_audioPlayer;
    e172::Vector<double> m_attachOffset;
    e172::ElapsedTimer m_timer = e172::ElapsedTimer(100);
};

} // namespace proj172::core
