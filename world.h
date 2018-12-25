#ifndef WORLD_H
#define WORLD_H


#include "assetmanager.h"
#include "units/camera.h"
#include "capabilities/player.h"
#include "capabilities/modulehandler.h"

class World : public Object
{
private:
    Camera *camera;
    Controller *player;

public:
    World();
    void init(AssetManager *assets, std::vector<Worker*> *units);
    Camera *getCamera();
};

#endif // WORLD_H
