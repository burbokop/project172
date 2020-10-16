#ifndef VISUALEFFECT_H
#define VISUALEFFECT_H

#include <SDL2/SDL.h>


#include <src/math/vector.h>


class VisualEffect {
protected:
    e172::Vector offset;
public:
    VisualEffect();
    VisualEffect(e172::Vector offset);
    virtual SDL_Surface *operator()(SDL_Surface *input);
    void setOffset(const e172::Vector &value);
    virtual ~VisualEffect();
};

#endif // VISUALEFFECT_H
