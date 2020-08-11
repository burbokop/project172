#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "gui/guimain.h"
#include "near.h"
#include "worlds/world.h"
#include "additional/informative/fpsmonitor.h"

#include <units/camera.h>


class WorldManager : public e172::Entity {
private:
    Camera *camera = nullptr;
    GUIMain *gui = nullptr;
    Near *_near = nullptr;
    e172::AbstractRenderer * m_renderer = nullptr;
    std::vector<World*> worlds;
    World *activeWorld = nullptr;
    bool worldIsChanged = true;

    void onChangeReset(old::Variant caseValue);
    void clear(std::list<e172::Entity *> *units);

    void init(e172::AssetProvider *assets, std::list<e172::Entity *> *units, e172::AbstractRenderer *renderer, FPSMonitor *fps, FPSMonitor *tps);
public:
    WorldManager(std::vector<World*> worlds);

    void checkState(e172::Context *context, e172::AssetProvider *assets, std::list<e172::Entity *> *units, e172::AbstractRenderer *renderer, FPSMonitor *fps, FPSMonitor *tps);

    Camera *getCamera() const;
    GUIMain *getGui() const;
    Near *getNear() const;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // WORLDMANAGER_H
