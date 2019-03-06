#ifndef ANIMATOR_H
#define ANIMATOR_H


#include "additional/timer.h"
#include "worker.h"

class Animator : public Worker {
public:
    static const unsigned PING_PONG;
    static const unsigned LOOP;
    static const unsigned ONEFRAME;
    static const unsigned FROZE;
    static const unsigned NOTRENDER;
    static const unsigned TOTHEFRAME;
    static const unsigned DEFAULT_INACTIVE;


private:
    Vector pos;
    double angle;
    double zoom;


    unsigned mode = NOTRENDER;
    unsigned defaultMode = DEFAULT_INACTIVE;

    Timer timer = Timer(100);
    SDL_Surface *origin;
    std::vector<SDL_Surface*> frames;
    int maxFrame;
    int maxTrack;
    int currentFrame;
    int currentTrack;

public:
    Animator();
    Animator(SDL_Surface *origin, int frames = 1, int tracks = 1);
    void play(unsigned mode);
    void setDefaultMode(const Uint8 &value);
    void setPosition(Vector pos);
    void setAngle(double angle);
    void setZoom(double zoom);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // ANIMATOR_H
