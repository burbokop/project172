#ifndef MODULE_H
#define MODULE_H


#include "../capability.h"
#include <src/iinformative.h>
#include <src/utility/animator.h>
#include <src/audio/audioplayer.h>

class Module : public Capability, public IInformative {
protected:
    e172::Animator animator;
    e172::AudioPlayer audioPlayer;
    e172::Vector attachOffset;
    e172::ElapsedTimer timer = e172::ElapsedTimer(100);
public:
    Module();
    void animate(unsigned mode, unsigned def = e172::Animator::Inactive);

    // Entity interface
public:

    void proceed(e172::Context *, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *renderer);
};

#endif // MODULE_H
