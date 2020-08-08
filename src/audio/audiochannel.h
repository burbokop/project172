#ifndef AUDIOCHANNEL_H
#define AUDIOCHANNEL_H

#include <map>

#include "audio.h"


class AudioChannel {
public:
    static const int Infinitely;
private:
    static inline int nextChannel = 0;
    int ptr = 0;
    double m_volume = 1;
    double m_distance_volume = 1;

    double m_maxDistance = 1024;
    double m_minDistance = 128;
public:
    AudioChannel();

    void setVolume(double volume);
    void setDistance(double distance);

    void play(AudioSample *sample, int loops = 1);
    bool isPlaying();
    void stop();


    void setMaxDistance(double maxDistance);
    void setMinDistance(double minDistance);
    double maxDistance() const;
    double minDistance() const;
};

#endif // AUDIOCHANNEL_H
