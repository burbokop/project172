#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <worker.h>


struct Star {
    Vector pos;
    Uint32 color;
};

class Background : public Worker {
private:
    static const double STARS_SLIDING_SPEED;

    Uint32 mainColor;
    std::vector<Star> stars;
    Vector *resolution;
    Vector speed;
    double slidingStart;

public:
    Background(Vector *resolution);
    void init(unsigned int amount, double slidingStart = STARS_SLIDING_SPEED);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
    void setSpeed(const Vector &value);
};

#endif // BACKGROUND_H
