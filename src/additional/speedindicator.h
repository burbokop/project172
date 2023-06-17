#pragma once

#include <src/graphics/abstractrenderer.h>

class SpeedIndicator {
public:
    SpeedIndicator() = default;

    void render(e172::AbstractRenderer *renderer);

private:
    int m_number = 0;
    int m_lastNumber = 0;
    int m_position = 0;
};
