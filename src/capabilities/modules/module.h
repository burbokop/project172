#ifndef MODULE_H
#define MODULE_H


#include "capabilities/capability.h"
#include "loadable.h"
#include "iinformative.h"



class Module : public Capability, public Loadable, public IInformative {
public:
    Module();
    Module(Loadable *tmp);

    // Worker interface
public:

    void animate(Uint8 mode, Uint8 def);

    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // MODULE_H
