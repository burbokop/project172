#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <worker.h>


struct Star {
    Vector pos;
    Uint32 color;
};

class Background : public Worker
{
    Uint32 mainColor;
    std::vector<Star> stars;
    Vector *resolution;

public:
    Background(Vector *resolution);
    void init(unsigned int amount);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // BACKGROUND_H
