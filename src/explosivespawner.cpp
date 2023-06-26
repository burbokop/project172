#include "explosivespawner.h"

#include <math.h>
#include <src/additional/lightparticle.h>
#include <src/context.h>
#include <src/messagetype.h>

namespace proj172::core {

void ExplosiveSpawner::spawnExplosive(e172::Context *context, const e172::Variant &value) {
    const auto vector = value.toVector();
    if(vector.size() > 1) {
        spawnExplosive(context,
                       vector[0].toMathVector<double>(),
                       vector[1].toMathVector<double>(),
                       vector[2].toInt());
    }
}

void ExplosiveSpawner::spawnExplosive(e172::Context *context, const e172::Vector<double> &position, const e172::Vector<double> &velocity, int radius) {
    const int v0 = static_cast<int>(std::sqrt(radius)) * 350;
    for(int i = 0; i < radius * 4; i++) {
        unsigned types[] = { LightParticle::PIXEL, LightParticle::CIRCLE, LightParticle::SQUARE };
        LightParticle *particle = e172::FactoryMeta::make<LightParticle>(types[rand() % 3],
                                                                         radius * 600,
                                                                         radius * 400);

        particle->place(position,
                        e172::Vector<double>::createRandom(e172::Random::uniq(), 0, v0) + velocity);
        context->addEntity(particle);
    }
}

void ExplosiveSpawner::proceed(e172::Context *context, e172::EventHandler *)
{
    context->popMessage(~MessageType::SpawnExplosive, this, &ExplosiveSpawner::spawnExplosive);
}

} // namespace proj172::core
