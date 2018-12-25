#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "worker.h"
#include "additional/timer.h"
#include "spm.h"

class Animator : public Worker
{
public:
    static const Uint8 PING_PONG;
    static const Uint8 LOOP;
    static const Uint8 ONEFRAME;
    static const Uint8 FROZE;
    static const Uint8 NOTRENDER;
    static const Uint8 TOTHEFRAME;


private:
    Vector pos;
    double angle;
    double zoom;


    Uint8 mode = NOTRENDER;
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
    void play(Uint8 mode);
    void setPosition(Vector pos);
    void setAngle(double angle);
    void setZoom(double zoom);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // ANIMATOR_H
