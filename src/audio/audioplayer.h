#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include <engine/audio/audiochannel.h>


class AudioPlayer {
public:
    enum State {
        Idle,
        Beginning,
        Loop,
        Ending
    };

private:
    e172::AudioChannel m_channel;
    unsigned state = Idle;
    bool m_waitStopPlaing = false;

    e172::AudioSample beginningSample;
    e172::AudioSample loopSample;
    e172::AudioSample endingSample;


    static inline int nextId = 0;
    int id = nextId++;
public:
    AudioPlayer(
            const e172::AudioChannel channel = e172::AudioChannel(),
            const e172::AudioSample &start = e172::AudioSample(),
            const e172::AudioSample &loop = e172::AudioSample(),
            const e172::AudioSample &stop = e172::AudioSample()
            );

    // Entity interface
public:
    bool play();
    bool stop();

    void proceed();

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
