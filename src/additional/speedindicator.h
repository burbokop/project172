#pragma once

#include <e172/graphics/abstractrenderer.h>

namespace proj172::core {

class SpeedIndicator {
public:
    SpeedIndicator() = default;

    void render(e172::AbstractRenderer *renderer);

private:
    int m_number = 0;
    int m_lastNumber = 0;
    int m_position = 0;
};

} // namespace proj172::core
