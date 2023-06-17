#include "world.h"

namespace proj172::core {

WorldPreset::WorldPreset() {}

WorldPreset::~WorldPreset() {}

WorldPreset::GenerationResult &operator +=(WorldPreset::GenerationResult &r0, const WorldPreset::GenerationResult &r1) {
    for(const auto &c : r1.controllers) {
        r0.controllers.push_back(c);
    }
    for(const auto &c : r1.entities) {
        r0.entities.push_back(c);
    }
    return r0;
}

} // namespace proj172::core
