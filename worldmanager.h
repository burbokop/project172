#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "units/camera.h"
#include "gui/guimain.h"
#include "worlds/world.h"

class WorldManager : public Object {
private:
    Camera *camera;
    GUIMain *gui;

    std::vector<World*> worlds;
    World *activeWorld;
    bool worldIsChanged;

    void onChangeReset(Auto caseValue);
    void clear(std::vector<Worker *> *units);
public:
    WorldManager(std::vector<World*> worlds);

    void init(Context *context, AssetManager *assets, std::vector<Worker *> *units, Renderer *renderer, FPSMonitor *fps);

    void checkState(Context *context, AssetManager *assets, std::vector<Worker *> *units, Renderer *renderer, FPSMonitor *fps);

    Camera *getCamera() const;
    GUIMain *getGui() const;



};

#endif // WORLDMANAGER_H
