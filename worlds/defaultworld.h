#ifndef DEFAULTWORLD_H
#define DEFAULTWORLD_H

#include "world.h"

class DefaultWorld : public World {
public:
    DefaultWorld();

    // World interface
public:
    std::vector<Controller *> generate(AssetManager *assets, std::vector<Worker *> *units);
    std::string getName();
};

#endif // DEFAULTWORLD_H
