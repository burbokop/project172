#ifndef ENGINE_H
#define ENGINE_H

#include "capabilities/modules/module.h"

class Engine : public Module {
public:
    Engine();
    Engine(Loadable *tmp);


    // Worker interface
public:
    bool forward();
    void stop();


    void tick(Context *context, e172::AbstractEventHandler *eventHandler);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // ENGINE_H
