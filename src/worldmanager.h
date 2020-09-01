#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "gui/guimain.h"
#include "near.h"
#include "worlds/world.h"
#include "additional/informative/fpsmonitor.h"

#include <src/units/camera.h>

#include <src/engine/memcontrol/abstractstrategy.h>


class WorldPresetStrategy : public e172::Entity {
    e172::AbstractStrategy<std::string, WorldPreset> m_strategy;
    WorldPreset *m_last = nullptr;

public:
    WorldPresetStrategy();

    template<typename T>
    void registerType() { m_strategy.registerType<T>(); }
    std::list<std::string> presetNames() const;

    void activatePreset(const std::string &preset);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *) override;
};

#endif // WORLDMANAGER_H
