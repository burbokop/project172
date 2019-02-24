#ifndef AUDIOCHANNEL_H
#define AUDIOCHANNEL_H

#include <map>

#include "audio.h"


class AudioChannel {
public:
    static const int INFINITELY;

    static int channelsReserved;

private:
    int ptr = 0;
    int volumeValue = 0;

    bool deadChannel = true;
    void allocate();
public:
    AudioChannel();
    static AudioChannel createChannel();

    bool isAvailable();
    void volume(int volume);
    void play(AudioSample *sample, int loops = 1);
    bool isPlaying();
    void stop();
    void free();
    ~AudioChannel();
};

#endif // AUDIOCHANNEL_H
