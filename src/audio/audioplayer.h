#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include "audio/audiochannel.h"
#include "worker.h"


class AudioPlayer : public Worker {
public:
    static const unsigned NONE;
    static const unsigned START_PLAYING;
    static const unsigned LOOP_PLAYING;
    static const unsigned STOP_PLAYING;

    static const int CUT_VOLUME_DISTANCE;
    static const int FULL_VOLUME_DISTANCE;
private:
    AudioChannel channel;
    unsigned state = NONE;

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
    void play();
    void stop();


    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);

    void setVolume(int volume);
    void setVolumeByDistance(double distance);

    friend bool operator ==(const AudioPlayer& ap0, const AudioPlayer& ap1);
};

#endif // AUDIOPLAYER_H
