#include "audioplayer.h"
#include "units/camera.h"
#include <engine/math/math.h>



void AudioPlayer::setWaitStopPlaing(bool waitStopPlaing) {
    m_waitStopPlaing = waitStopPlaing;
}

AudioPlayer::AudioPlayer(const e172::AudioChannel channel, const e172::AudioSample &start, const e172::AudioSample &loop, const e172::AudioSample &stop) {
    m_channel = channel;
    beginningSample = start;
    loopSample = loop;
    endingSample = stop;
}


bool AudioPlayer::play() {
    if(state == Idle || !m_waitStopPlaing) {
        m_channel.play(beginningSample, 1);
        state = Beginning;
        return true;
    }
    return false;
}

bool AudioPlayer::stop() {
    if(state == Beginning || state == Loop) {
        m_channel.play(endingSample, 1);
        state = Ending;
        return true;
    }
    return false;
}

void AudioPlayer::proceed() {
    if(state == Beginning) {
        if(!m_channel.isPlaying()) {
            if(loopSample.isValid()) {
                m_channel.play(loopSample, e172::AudioChannel::Infinitely);
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

void AudioPlayer::setVolume(double volume) {
    m_channel.setVolume(volume);
}

void AudioPlayer::setDistance(double distance) {
    m_channel.setDistance(distance);
}

bool operator ==(const AudioPlayer &ap0, const AudioPlayer &ap1) {
    return ap0.id == ap1.id;
}
