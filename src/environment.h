#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>


#include "object.h"
#include "state.h"
#include "renderer.h"
#include "worker.h"
#include "assetmanager.h"
#include "additional/event.h"
#include "background.h"
#include "additional/informative/fpsmonitor.h"
#include "netlistener.h"
#include "worldmanager.h"
#include "additional/mutex.h"


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
    FPSMonitor *tps = nullptr;
    NetListener *netListener = nullptr;
    WorldManager *worldManager = nullptr;

public:
    Environment(std::vector<std::string> args);
    void start();
    void quit();
};

#endif // ENVIRONMENT_H
