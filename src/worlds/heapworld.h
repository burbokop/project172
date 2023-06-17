#pragma once

#include "world.h"

namespace proj172::core {

class HeapWorld : public WorldPreset {
public:
    HeapWorld();

    // World interface
public:
    virtual GenerationResult generate(e172::Context *context) override;
};

} // namespace proj172::core
