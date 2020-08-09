#ifndef AUDIOCHANNEL_H
#define AUDIOCHANNEL_H

#include <map>

#include "audiosample.h"

namespace e172 {

class AudioChannel : public SharedContainer {
    friend class AbstractAudioProvider;
public:
    static const int Infinitely;
    typedef std::function<void(data_ptr, double)> volume_setter_t;
    typedef std::function<void(data_ptr, const AudioSample&, int)> play_t;
    typedef std::function<bool(data_ptr)> is_playing_t;
    typedef std::function<void(data_ptr)> pause_t;
    static AudioChannel newAudioChannel(
            data_ptr data,
            ptr id,
            destructor_t destructor,
            volume_setter_t volume_setter,
            play_t play,
            is_playing_t is_palying,
            pause_t pause
            );
private:
    volume_setter_t m_volume_setter;
    play_t m_play;
    is_playing_t m_is_palying;
    pause_t m_pause;

    double m_volume = 1;
    double m_distance_volume = 1;

    double m_maxDistance = 1024;
    double m_minDistance = 128;
public:
    AudioChannel();

    void setVolume(double volume);
    void setDistance(double distance);

    void play(const AudioSample &sample, int loops = 1);
    bool isPlaying();
    void stop();

    void setMaxDistance(double maxDistance);
    void setMinDistance(double minDistance);
    double maxDistance() const;
    double minDistance() const;
};

}

#endif // AUDIOCHANNEL_H
