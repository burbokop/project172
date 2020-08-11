#ifndef HEAPWORLD_H
#define HEAPWORLD_H


#include "worlds/world.h"


class HeapWorld : public World {
public:
    HeapWorld();

    // World interface
public:
    std::vector<Controller *> generate(e172::AssetProvider *assets, std::list<e172::Entity*> *units);
    std::string getName();
};

#endif // HEAPWORLD_H
