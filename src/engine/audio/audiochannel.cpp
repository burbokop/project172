#include "audiochannel.h"

#include <iostream>

#include <src/engine/math/math.h>

namespace e172 {


const int AudioChannel::Infinitely = -1;


void AudioChannel::setMaxDistance(double maxDistance)
{
    m_maxDistance = maxDistance;
}

void AudioChannel::setMinDistance(double minDistance)
{
    m_minDistance = minDistance;
}

double AudioChannel::maxDistance() const
{
    return m_maxDistance;
}

double AudioChannel::minDistance() const
{
    return m_minDistance;
}

AudioChannel AudioChannel::newAudioChannel(SharedContainer::data_ptr data, SharedContainer::ptr id, SharedContainer::destructor_t destructor, AudioChannel::volume_setter_t volume_setter, AudioChannel::play_t play, is_playing_t is_palying, pause_t pause) {
    auto result = newSharedContainer<AudioChannel>(data, id, destructor);
    result.m_play = play;
    result.m_volume_setter = volume_setter;
    result.m_is_palying = is_palying;
    result.m_pause = pause;
    return result;
}

AudioChannel::AudioChannel() {}

void AudioChannel::setVolume(double volume) {
    m_volume = volume;
}

void AudioChannel::play(const AudioSample &sample, int loops) {
    if(isValid()) {
        const auto v = m_volume * m_distance_volume;
        if(m_volume_setter)
            m_volume_setter(data(), v);

        if(v > 0 && sample.isValid()) {
            m_play(data(), sample, loops);
        }
    }
}

bool AudioChannel::isPlaying() {
    if(m_is_palying)
        return m_is_palying(data());

    return false;
}

void AudioChannel::stop() {
    if(m_pause)
        m_pause(data());
}

void AudioChannel::setDistance(double distance) {
    if(distance < m_minDistance) distance = m_minDistance;
    if(distance > m_maxDistance) distance = m_maxDistance;
    m_distance_volume = e172::Math::map(distance, m_minDistance, m_maxDistance, 1, 0);
}

}
