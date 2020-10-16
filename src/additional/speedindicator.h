#ifndef SPEEDINDICATOR_H
#define SPEEDINDICATOR_H

#include <src/graphics/abstractrenderer.h>

class SpeedIndicator {
    int number = 0;
    int lastNumber = 0;
    int position = 0;
public:
    SpeedIndicator();

    void render(e172::AbstractRenderer *renderer);
};

#endif // SPEEDINDICATOR_H
