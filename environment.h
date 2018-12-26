#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <SDL2/SDL.h>

#include "units/unit.h"
#include "world.h"
#include "additional/event.h"
#include "context.h"
#include "background.h"

class Environment : public Object
{
private:
    Vector *resolution;
    Renderer *renderer;
    std::vector<Worker*> *units;
    AssetManager *assetManager;
    Context *context;
    Event *event;
    World world;
    Background *background;

public:
    Environment();
    void init(int argc, char *argv[]);
    void start();
    void quit();
};

#endif // ENVIRONMENT_H
