#ifndef HEAPWORLD_H
#define HEAPWORLD_H


#include "world.h"


class HeapWorld : public WorldPreset {
public:
    HeapWorld();

    // World interface
public:
    virtual GenerationResult generate(e172::Context *context) override;
};

#endif // HEAPWORLD_H
