#ifndef MODULE_H
#define MODULE_H


#include "capabilities/capability.h"
#include "loadable.h"
#include "iinformative.h"



class Module : public Capability, public Loadable, public IInformative {
public:
    Module();
    Module(Loadable *tmp);

public:

    void animate(unsigned mode, unsigned def = Animator::DEFAULT_INACTIVE);


    // Worker interface
public:


    void tick(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // MODULE_H
