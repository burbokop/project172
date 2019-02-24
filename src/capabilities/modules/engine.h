#ifndef ENGINE_H
#define ENGINE_H

#include "capabilities/modules/module.h"

class Engine : public Module {
public:
    Engine();
    Engine(Loadable *tmp);


    // Worker interface
public:
    void loop(Context *context, Event *event);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // ENGINE_H
