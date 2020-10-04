#include "audioplayer.h"


#include <src/units/camera.h>
#include <src/engine/math/math.h>

void e172::AudioPlayer::setWaitStopPlaing(bool waitStopPlaing) {
    m_waitStopPlaing = waitStopPlaing;
}

e172::AudioSample e172::AudioPlayer::beginningSample() const {
    return m_beginningSample;
}

e172::AudioSample e172::AudioPlayer::loopSample() const {
    return m_loopSample;
}

e172::AudioSample e172::AudioPlayer::endingSample() const {
    return m_endingSample;
}

e172::AudioChannel e172::AudioPlayer::channel() const {
    return m_channel;
}

e172::AudioPlayer::AudioPlayer(const e172::AudioChannel channel, const e172::AudioSample &start, const e172::AudioSample &loop, const e172::AudioSample &stop) {
    m_channel = channel;
    m_beginningSample = start;
    m_loopSample = loop;
    m_endingSample = stop;
}


bool e172::AudioPlayer::play() {
    if(state == Idle || !m_waitStopPlaing) {
        m_channel.play(m_beginningSample, 1);
        state = Beginning;
        return true;
    }
    return false;
}

bool e172::AudioPlayer::stop() {
    if(state == Beginning || state == Loop) {
        m_channel.play(m_endingSample, 1);
        state = Ending;
        return true;
    }
    return false;
}

void e172::AudioPlayer::proceed() {
    if(state == Beginning) {
        if(!m_channel.isPlaying()) {
            if(m_loopSample.isValid()) {
                m_channel.play(m_loopSample, e172::AudioChannel::Infinitely);
                state = Loop;
            } else {
                state = Idle;
            }
        }
    } else if(state == Ending) {
        if(!m_channel.isPlaying()) {
            state = Idle;
        }
    }
}

void e172::AudioPlayer::setVolume(double volume) {
    m_channel.setVolume(volume);
}

void e172::AudioPlayer::setDistance(double distance) {
    m_channel.setDistance(distance);
}

namespace e172 {
bool operator ==(const e172::AudioPlayer &ap0, const e172::AudioPlayer &ap1) {
    return ap0.id == ap1.id;
}
}
