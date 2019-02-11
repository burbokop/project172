#ifndef ANAGLYPH_H
#define ANAGLYPH_H

#include <math.h>
#include "visualeffect.h"


class Anaglyph : public VisualEffect {
public:
    Anaglyph();
    Anaglyph(Vector offset);

// VisualEffect interface
public:
SDL_Surface *operator ()(SDL_Surface *input);

};

#endif // ANAGLYPH_H
