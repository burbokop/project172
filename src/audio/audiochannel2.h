#ifndef AUDIOCHANNEL2_H
#define AUDIOCHANNEL2_H

#include <functional>
#include <map>
#include "audio.h"

class AudioChannel2 {
public:
    static const int Infinitely;
private:
    static inline int nextChannel = 0;
    static int static_call;

    int ptr = -1;
    double m_volume = 1;
    double m_distance_volume = 1;

    double m_maxDistance = 1024;
    double m_minDistance = 128;

    bool m_isPlaying = false;
public:
    AudioChannel2();

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


#endif // AUDIOCHANNEL2_H
