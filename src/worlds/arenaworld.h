#ifndef ARENAWORLD_H
#define ARENAWORLD_H


#include "world.h"


class ArenaWorld : public WorldPreset {
public:
    ArenaWorld();

    // World interface
public:
    virtual GenerationResult generate(e172::Context *context) override;
};

#endif // ARENAWORLD_H
