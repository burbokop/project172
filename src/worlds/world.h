#ifndef WORLD_H
#define WORLD_H

#include <functional>

#include <assettools/assetmanager.h>


#include "../object.h"
#include "../capabilities/controller.h"


class World : public Object {
public:
    World();
    virtual std::vector<Controller*> generate(AssetManager *assets, std::vector<Worker*> *units) = 0;
    virtual std::string getName() = 0;

    virtual ~World();
};

#endif // WORLD_H
