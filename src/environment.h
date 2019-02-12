#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>

#include "units/unit.h"
#include "worldmanager.h"
#include "worlds/defaultworld.h"
#include "worlds/arenaworld.h"
#include "additional/event.h"
#include "context.h"
#include "background.h"
#include "netlistener.h"
#include "state.h"


class Environment : public Object {
private:
    State *state = nullptr;
    Renderer *renderer = nullptr;
    std::vector<Worker*> *units = nullptr;
    AssetManager *assetManager = nullptr;
    Context *context = nullptr;
    Event *event = nullptr;
    Background *background = nullptr;
    FPSMonitor *fps = nullptr;
    NetListener *netListener = nullptr;
    WorldManager *worldManager = nullptr;

public:
    Environment();
    void init(int argc, char *argv[]);
    void start();
    void quit();
};

#endif // ENVIRONMENT_H
