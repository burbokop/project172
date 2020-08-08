#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include "audio/audiochannel.h"
#include "audiochannel2.h"
#include "worker.h"


class AudioPlayer : public Worker {
public:
    enum State {
        Idle,
        Beginning,
        Loop,
        Ending
    };

private:
    AudioChannel channel;
    unsigned state = Idle;
    bool m_waitStopPlaing = false;

    AudioSample *startChunk = nullptr;
    AudioSample *loopChunk = nullptr;
    AudioSample *stopChunk = nullptr;


    static inline int nextId = 0;
    int id = nextId++;
public:
    AudioPlayer(AudioSample *start = nullptr, AudioSample *loop = nullptr, AudioSample *stop = nullptr);
    ~AudioPlayer();

    // Worker interface
public:
    bool play();
    bool stop();


    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);

    /**
     * @brief setVolume
     * @param volume - value in percent from 0 to 1
     */
    void setVolume(double volume);
    void setDistance(double distance);

    void setWaitStopPlaing(bool waitStopPlaing);

    friend bool operator ==(const AudioPlayer& ap0, const AudioPlayer& ap1);
};

#endif // AUDIOPLAYER_H
