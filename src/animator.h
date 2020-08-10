#ifndef ANIMATOR_H
#define ANIMATOR_H


#include "time/timer.h"
#include "worker.h"
#include <vector>

class Animator : public Worker {
public:
    enum {
        PING_PONG,
        LOOP,
        ONEFRAME,
        FROZE,
        NOTRENDER,
        TOTHEFRAME,
        DEFAULT_INACTIVE
    };
private:
    e172::Vector pos;
    double angle;
    double zoom;

    unsigned mode = NOTRENDER;
    unsigned defaultMode = DEFAULT_INACTIVE;

    Timer timer = Timer(100);
    e172::Image origin;
    std::vector<e172::Image> frames;
    int m_frameCount;
    int m_trackCount;
    int currentFrame;
    int currentTrack;
    bool m_isValid = false;

    static inline int nextId = 0;
    int id = nextId++;
public:
    Animator();
    Animator(const e172::Image &origin, int frames = 1, int tracks = 1);
    void play(unsigned mode);
    void setDefaultMode(unsigned value);
    void setPosition(e172::Vector pos);
    void setAngle(double angle);
    void setZoom(double zoom);

    // Worker interface
public:
    void tick(Context *context,  e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);


    friend bool operator ==(const Animator& anim0, const Animator& anim1);
    bool isValid() const;
    int frameCount() const;
    int trackCount() const;
};


#endif // ANIMATOR_H
