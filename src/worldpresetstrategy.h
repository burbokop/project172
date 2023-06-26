#pragma once

#include "worlds/world.h"
#include <src/units/camera.h>
#include <src/memcontrol/abstractstrategy.h>

namespace proj172::core {

class WorldPresetStrategy : public e172::Entity {
public:
    static inline const std::string WORLD_TAG = "W";

    WorldPresetStrategy(e172::FactoryMeta &&meta)
        : e172::Entity(std::move(meta))
    {}

    template<typename T>
    void registerType() { m_strategy.registerType<T>(); }
    std::list<std::string> presetNames() const;

    void activatePreset(const std::string &preset);

    void controllersChanged(const std::function<void (const std::list<e172::ptr<Controller> > &)> &callback);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *) override;

private:
    e172::AbstractStrategy<std::string, WorldPreset> m_strategy;
    WorldPreset *m_last = nullptr;
    std::function<void(const std::list<e172::ptr<Controller>> &)> m_controllersChangedCallback;
};

} // namespace proj172::core
