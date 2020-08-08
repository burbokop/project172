#include "audio.h"
#include "audiochannel2.h"

#include <engine/math/math.h>

const int AudioChannel2::Infinitely = -1;

std::map<int, std::function<void()>> __AudioChannel2_f_map;

static int static_call = []() -> int {
            Mix_ChannelFinished([](int i) {
                const auto it = __AudioChannel2_f_map.find(i);
                if(it != __AudioChannel2_f_map.end()) {
                    it->second();
                }
            });
            return 0;
        }();


void AudioChannel2::setMaxDistance(double maxDistance)
{
    m_maxDistance = maxDistance;
}

void AudioChannel2::setMinDistance(double minDistance)
{
    m_minDistance = minDistance;
}

double AudioChannel2::maxDistance() const
{
    return m_maxDistance;
}

double AudioChannel2::minDistance() const
{
    return m_minDistance;
}

AudioChannel2::AudioChannel2() {
    ptr = nextChannel++ % Audio::MAX_CHANNEL_COUNT;
}

void AudioChannel2::setVolume(double volume) {
    m_volume = volume;

    if(ptr >= 0)
        Mix_Volume(ptr, m_volume * m_distance_volume * Audio::MAX_MAPPED_VOLUME);
}

void AudioChannel2::play(AudioSample *sample, int loops) {
    if(ptr >= 0) {
        const auto v = m_volume * m_distance_volume * Audio::MAX_MAPPED_VOLUME;
        if(v > 0 && sample != nullptr) {
            if(loops > 0) {
                ptr = Mix_PlayChannel(-1, sample, loops - 1);
            } else if (loops == Infinitely) {
                ptr = Mix_PlayChannel(-1, sample, Infinitely);
            }

            m_isPlaying = true;
            if(ptr >= 0) {
                __AudioChannel2_f_map[ptr] = [this](){
                    m_isPlaying = false;
                };
            }
        }
        if(ptr >= 0)
            Mix_Volume(ptr, v);
    }
}

bool AudioChannel2::isPlaying() {
    return m_isPlaying;
}

void AudioChannel2::stop() {
    Mix_Pause(ptr);
}

void AudioChannel2::setDistance(double distance) {
    if(distance < m_minDistance) distance = m_minDistance;
    if(distance > m_maxDistance) distance = m_maxDistance;
    m_distance_volume = e172::Math::map(distance, m_minDistance, m_maxDistance, 1, 0);

    if(ptr >= 0)
        Mix_Volume(ptr, m_volume * m_distance_volume * Audio::MAX_MAPPED_VOLUME);
}
