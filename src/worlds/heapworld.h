#ifndef HEAPWORLD_H
#define HEAPWORLD_H


#include "worlds/world.h"


class HeapWorld : public WorldPreset {
public:
    HeapWorld();

    // World interface
public:
    virtual GenerationResult generate(e172::Context *context) override;
    std::string getName();
};

#endif // HEAPWORLD_H
