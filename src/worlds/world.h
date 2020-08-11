#ifndef WORLD_H
#define WORLD_H

#include <functional>

#include <engine/assettools/assetprovider.h>


#include "../object.h"
#include "../capabilities/controller.h"


class World : public Object {
public:
    World();
    virtual std::vector<Controller*> generate(e172::AssetProvider *assets, std::list<e172::Entity*> *units) = 0;
    virtual std::string getName() = 0;

    virtual ~World();
};

#endif // WORLD_H
