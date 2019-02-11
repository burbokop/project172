#ifndef ARENAWORLD_H
#define ARENAWORLD_H

#include "world.h"

class ArenaWorld : public World {
public:
    ArenaWorld();

    // World interface
public:
    std::vector<Controller *> generate(AssetManager *assets, std::vector<Worker *> *units);
    std::string getName();
};

#endif // ARENAWORLD_H
