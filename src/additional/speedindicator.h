#ifndef SPEEDINDICATOR_H
#define SPEEDINDICATOR_H

#include <engine/graphics/abstractrenderer.h>

class SpeedIndicator {
    int number = 0;
    int lastNumber = 0;
    int position = 0;
public:
    SpeedIndicator();

    void render(e172::AbstractRenderer *renderer);
};

#endif // SPEEDINDICATOR_H
