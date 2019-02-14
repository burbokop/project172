#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "units/camera.h"
#include "gui/guimain.h"
#include "gui/guilist.h"
#include "worlds/world.h"
#include "near.h"

class WorldManager : public Object {
private:
    Camera *camera = nullptr;
    GUIMain *gui = nullptr;
    Near *near = nullptr;

    std::vector<World*> worlds;
    World *activeWorld = nullptr;
    bool worldIsChanged = true;

    void onChangeReset(Auto caseValue);
    void clear(std::vector<Worker *> *units);

    void init(AssetManager *assets, std::vector<Worker *> *units, Renderer *renderer, FPSMonitor *fps);
public:
    WorldManager(std::vector<World*> worlds);

    void checkState(Context *context, AssetManager *assets, std::vector<Worker *> *units, Renderer *renderer, FPSMonitor *fps);

    Camera *getCamera() const;
    GUIMain *getGui() const;
    Near *getNear() const;
};

#endif // WORLDMANAGER_H
