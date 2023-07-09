#pragma once

#include "../capabilities/controller.h"
#include <e172/assettools/assetprovider.h>
#include <functional>

namespace proj172::core {

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

WorldPreset::GenerationResult &operator+=(WorldPreset::GenerationResult &r0, const WorldPreset::GenerationResult& r1);

} // namespace proj172::core

