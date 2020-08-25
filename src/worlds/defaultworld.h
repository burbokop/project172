#ifndef DEFAULTWORLD_H
#define DEFAULTWORLD_H


#include "world.h"


class DefaultWorld : public WorldPreset {
public:
    DefaultWorld();

    // World interface
public:
    virtual GenerationResult generate(e172::Context *context) override;
};

#endif // DEFAULTWORLD_H
