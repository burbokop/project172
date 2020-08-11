#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>




#include "object.h"
#include "state.h"

#include "background.h"
#include "additional/informative/fpsmonitor.h"
#include "netlistener.h"
#include "worldmanager.h"
#include "additional/mutex.h"


class Environment : public Object {
private:
    State *state = nullptr;
    std::list<e172::Entity*> m_entities;
    e172::AssetProvider *assetManager = nullptr;
    e172::Context *context = nullptr;
    e172::AbstractEventHandler *eventHandler = nullptr;
    Background *background = nullptr;
    FPSMonitor *fps = nullptr;
    FPSMonitor *tps = nullptr;
    NetListener *netListener = nullptr;
    WorldManager *worldManager = nullptr;
    e172::AbstractGraphicsProvider *renderEngine = nullptr;
    e172::AbstractRenderer *renderer = nullptr;

public:
    Environment(std::vector<std::string> args);
    void start();
    void quit();
};

#endif // ENVIRONMENT_H
