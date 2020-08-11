#ifndef ANIMATOR_H
#define ANIMATOR_H


#include <vector>
#include <engine/math/vector.h>
#include <engine/time/elapsedtimer.h>
#include <engine/graphics/image.h>

namespace e172 { class AbstractRenderer; };

class Animator {
public:
    enum {
        PingPong,
        Loop,
        OneFrame,
        Froze,
        NotRender,
        ToTheFrame,
        Inactive
    };
private:
    e172::Vector pos;
    double angle;
    double zoom;

    unsigned mode = NotRender;
    unsigned defaultMode = Inactive;

    e172::ElapsedTimer timer = e172::ElapsedTimer(100);
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

    // Entity interface
public:
    void render(e172::AbstractRenderer *renderer);


    friend bool operator ==(const Animator& anim0, const Animator& anim1);
    bool isValid() const;
    int frameCount() const;
    int trackCount() const;
};


#endif // ANIMATOR_H
