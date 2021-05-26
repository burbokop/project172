#ifndef WORLD_H
#define WORLD_H

#include <functional>

#include <src/assettools/assetprovider.h>

#include "../capabilities/controller.h"


class WorldPreset {
public:
    struct GenerationResult {
        std::list<e172::ptr<e172::Entity>> entities;
        std::list<e172::ptr<Controller>> controllers;
    };

    WorldPreset();
    virtual GenerationResult generate(e172::Context *context) = 0;

    virtual ~WorldPreset();
};

#endif // WORLD_H
