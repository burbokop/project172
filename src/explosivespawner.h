#ifndef EXPLOSIVESPAWNER_H
#define EXPLOSIVESPAWNER_H

#include <src/engine/entity.h>



class ExplosiveSpawner : public e172::Entity {


    void spawnExplosive(e172::Context *context, const e172::Variant& value);
    void spawnExplosive(e172::Context *context, const e172::Vector &position, const e172::Vector &velocity, int radius);

    void spawnDirectExplosive(e172::Context *context, const e172::Variant& value);
public:
    ExplosiveSpawner();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *) {}
};

#endif // EXPLOSIVESPAWNER_H
