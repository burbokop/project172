#ifndef WORLDPRESETSTRATEGY_H
#define WORLDPRESETSTRATEGY_H


#include "gui/guimain.h"
#include "near.h"
#include "worlds/world.h"

#include <src/units/camera.h>

#include <src/memcontrol/abstractstrategy.h>



class WorldPresetStrategy : public e172::Entity {
    e172::AbstractStrategy<std::string, WorldPreset> m_strategy;
    WorldPreset *m_last = nullptr;

    std::function<void(const std::list<Controller*>&)> controllersChangedCallback;
public:
    static inline const std::string WORLD_TAG = "W";

    WorldPresetStrategy();

    template<typename T>
    void registerType() { m_strategy.registerType<T>(); }
    std::list<std::string> presetNames() const;

    void activatePreset(const std::string &preset);

    void controllersChanged(const std::function<void(const std::list<Controller*>&)>& callback);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *) override;
};

#endif // WORLDMANAGER_H
