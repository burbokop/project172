#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include "audio/audiochannel.h"
#include "worker.h"


class AudioPlayer : public Worker {
public:
    static Uint8 NONE;
    static Uint8 START_PLAYING;
    static Uint8 LOOP_PLAYING;
    static Uint8 STOP_PLAYING;

    static int CUT_VOLUME_DISTANCE;
    static int FULL_VOLUME_DISTANCE;


private:
    AudioChannel channel;
    Uint8 state = NONE;
    bool playPressed = false;

    AudioSample *startChunk = nullptr;
    AudioSample *loopChunk = nullptr;
    AudioSample *stopChunk = nullptr;

public:
    AudioPlayer(AudioSample *start = nullptr, AudioSample *loop = nullptr, AudioSample *stop = nullptr);

    // Worker interface
public:
    void play();
    void stop();


    void loop(Context *context, Event *event);
    void render(Renderer *renderer);

    void setVolume(int volume);
    void setVolumeByDistance(double distance);
};

#endif // AUDIOPLAYER_H
