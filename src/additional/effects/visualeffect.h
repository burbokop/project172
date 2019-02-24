#ifndef VISUALEFFECT_H
#define VISUALEFFECT_H

#include <SDL2/SDL.h>


#include "additional/vector.h"


class VisualEffect {
protected:
    Vector offset;
public:
    VisualEffect();
    VisualEffect(Vector offset);
    virtual SDL_Surface *operator()(SDL_Surface *input);
    void setOffset(const Vector &value);
    virtual ~VisualEffect();
};

#endif // VISUALEFFECT_H
