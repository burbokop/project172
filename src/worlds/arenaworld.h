#ifndef ARENAWORLD_H
#define ARENAWORLD_H


#include "worlds/world.h"


class ArenaWorld : public World {
public:
    ArenaWorld();

    // World interface
public:
    std::vector<Controller *> generate(e172::AssetProvider *assets, std::list<e172::Entity*> *units);
    std::string getName();
};

#endif // ARENAWORLD_H
