#include "explosivespawner.h"

#include <math.h>

#include <src/engine/context.h>

#include <src/additional/lightparticle.h>

void ExplosiveSpawner::spawnExplosive(e172::Context *context, const e172::Variant &value) {
    const auto vector = value.toVector();
    if(vector.size() > 1) {
        spawnExplosive(context, vector[0].toMathVector(), vector[1].toMathVector(), vector[2].toInt());
    }
}

void ExplosiveSpawner::spawnExplosive(e172::Context *context, const e172::Vector& position, const e172::Vector& velocity, int radius) {
    const int v0 = static_cast<int>(std::sqrt(radius)) * 350;
    for(int i = 0; i < radius * 4; i++) {
        unsigned types[] = { LightParticle::PIXEL, LightParticle::CIRCLE, LightParticle::SQUARE };
        LightParticle *particle = new LightParticle(types[rand() % 3], radius * 600, radius * 400);
        particle->place(position, e172::Vector::createRandom(v0) + velocity);
        context->addEntity(particle);
    }
}


ExplosiveSpawner::ExplosiveSpawner() {}


void ExplosiveSpawner::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    context->popMessage(
                e172::Context::SPAWN_EXPLOSIVE,
                this,
                &ExplosiveSpawner::spawnExplosive
                );
}
