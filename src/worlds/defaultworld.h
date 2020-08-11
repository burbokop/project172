#ifndef DEFAULTWORLD_H
#define DEFAULTWORLD_H


#include "worlds/world.h"


class DefaultWorld : public World {
public:
    DefaultWorld();

    // World interface
public:
    std::vector<Controller *> generate(e172::AssetProvider *assets, std::list<e172::Entity*> *units);
    std::string getName();
};

#endif // DEFAULTWORLD_H
