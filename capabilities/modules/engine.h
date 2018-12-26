#ifndef ENGINE_H
#define ENGINE_H

#include "module.h"

class Engine : public Module {
public:
    Engine();
    Engine(Loadable *tmp);


    // Worker interface
public:
    void loop(Context *context, Event *event);
};

#endif // ENGINE_H
