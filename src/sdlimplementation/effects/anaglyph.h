#ifndef ANAGLYPH_H
#define ANAGLYPH_H

#include "visualeffect.h"

#include <math.h>


class Anaglyph : public VisualEffect {
public:
    Anaglyph();
    Anaglyph(e172::Vector offset);

// VisualEffect interface
public:
SDL_Surface *operator ()(SDL_Surface *input);

};

#endif // ANAGLYPH_H
