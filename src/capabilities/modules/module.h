#ifndef MODULE_H
#define MODULE_H


#include "capabilities/capability.h"
#include "iinformative.h"

#include <engine/assettools/loadable.h>

#include <animator.h>

#include <audio/audioplayer.h>



class Module : public Capability, public e172::Loadable, public IInformative {
protected:
    Animator animator;
    AudioPlayer audioPlayer;
    e172::Vector attachOffset;
    e172::ElapsedTimer timer = e172::ElapsedTimer(100);
public:
    Module();
    void animate(unsigned mode, unsigned def = Animator::Inactive);

    // Entity interface
public:

    void proceed(e172::Context *, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *renderer);
};

#endif // MODULE_H
