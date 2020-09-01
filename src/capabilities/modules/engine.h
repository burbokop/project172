#ifndef ENGINE_H
#define ENGINE_H

#include "module.h"

class Engine : public Module {
public:
    Engine();
    Engine(Loadable *tmp);


    // Entity interface
public:
    bool forward();
    void stop();


    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // ENGINE_H
