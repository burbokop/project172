#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "gui/guimain.h"
#include "near.h"
#include "worlds/world.h"
#include "additional/informative/fpsmonitor.h"


class WorldManager : public Object {
private:
    Camera *camera = nullptr;
    GUIMain *gui = nullptr;
    Near *near = nullptr;

    std::vector<World*> worlds;
    World *activeWorld = nullptr;
    bool worldIsChanged = true;

    void onChangeReset(Variant caseValue);
    void clear(std::vector<Worker*> *units);

    void init(AssetManager *assets, std::vector<Worker*> *units, Renderer *renderer, FPSMonitor *fps, FPSMonitor *tps);
public:
    WorldManager(std::vector<World*> worlds);

    void checkState(Context *context, AssetManager *assets, std::vector<Worker*> *units, Renderer *renderer, FPSMonitor *fps, FPSMonitor *tps);

    Camera *getCamera() const;
    GUIMain *getGui() const;
    Near *getNear() const;
};

#endif // WORLDMANAGER_H
