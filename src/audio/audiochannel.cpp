#include "audiochannel.h"

#include <iostream>

#include <engine/math/math.h>

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

AudioChannel::AudioChannel() {
    ptr = nextChannel++ % Audio::MAX_CHANNEL_COUNT;
}

void AudioChannel::setVolume(double volume) {
    m_volume = volume;
}

void AudioChannel::play(AudioSample *sample, int loops) {
    if(ptr >= 0) {
        const auto v = m_volume * m_distance_volume * Audio::MAX_MAPPED_VOLUME;
        Mix_Volume(ptr, v);
        if(v > 0 && sample != nullptr) {
            if(loops > 0) {
                Mix_PlayChannel(ptr, sample, loops - 1);
            } else if (loops == Infinitely) {
                Mix_PlayChannel(ptr, sample, Infinitely);
            }
        }
    }
}

bool AudioChannel::isPlaying() {
    return Mix_Playing(ptr);
}

void AudioChannel::stop() {
    Mix_Pause(ptr);
}

void AudioChannel::setDistance(double distance) {
    if(distance < m_minDistance) distance = m_minDistance;
    if(distance > m_maxDistance) distance = m_maxDistance;
    m_distance_volume = e172::Math::map(distance, m_minDistance, m_maxDistance, 1, 0);
}
