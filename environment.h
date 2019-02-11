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
    State *state;
    Renderer *renderer;
    std::vector<Worker*> *units;
    AssetManager *assetManager;
    Context *context;
    Event *event;
    Background *background;
    FPSMonitor *fps;
    NetListener *netListener;
    WorldManager *worldManager;

public:
    Environment();
    void init(int argc, char *argv[]);
    void start();
    void logic();
    void quit();
};

#endif // ENVIRONMENT_H
