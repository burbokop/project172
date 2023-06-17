#pragma once

#include <src/entity.h>
#include <src/math/vector.h>

namespace proj172::core {

class ExplosiveSpawner : public e172::Entity {
public:
    ExplosiveSpawner(e172::FactoryMeta &&meta)
        : e172::Entity(std::move(meta))
    {}

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *);
    void render(e172::AbstractRenderer *) {}

private:
    void spawnExplosive(e172::Context *context, const e172::Variant &value);
    void spawnExplosive(e172::Context *context,
                        const e172::Vector<double> &position,
                        const e172::Vector<double> &velocity,
                        int radius);

    void spawnDirectExplosive(e172::Context *context, const e172::Variant &value);
};

} // namespace proj172::core
