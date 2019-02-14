#ifndef HEAPWORLD_H
#define HEAPWORLD_H

#include "world.h"
#include "capabilities/aggressive.h"

class HeapWorld : public World {
public:
    HeapWorld();

    // World interface
public:
    std::vector<Controller *> generate(AssetManager *assets, std::vector<Worker *> *units);
    std::string getName();
};

#endif // HEAPWORLD_H
