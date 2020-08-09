#include "audioplayer.h"
#include "units/camera.h"
#include <engine/math/math.h>



void AudioPlayer::setWaitStopPlaing(bool waitStopPlaing) {
    m_waitStopPlaing = waitStopPlaing;
}

AudioPlayer::AudioPlayer(const e172::AudioSample &start, const e172::AudioSample &loop, const e172::AudioSample &stop) {
    this->startChunk = start;
    this->loopChunk = loop;
    this->stopChunk = stop;
}


bool AudioPlayer::play() {
    if(state == Idle || !m_waitStopPlaing) {
        channel.play(startChunk, 1);
        state = Beginning;
        return true;
    }
    return false;
}

bool AudioPlayer::stop() {
    if(state == Beginning || state == Loop) {
        channel.play(stopChunk, 1);
        state = Ending;
        return true;
    }
    return false;
}

#include <iostream>
void AudioPlayer::tick(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);

    if(state == Beginning) {
        if(!channel.isPlaying()) {
            std::cout << "LOOP STRT\n";
            if(loopChunk.isValid()) {
                channel.play(loopChunk, e172::AudioChannel::Infinitely);
                state = Loop;
            } else {
                state = Idle;
            }
        }
    } else if(state == Ending) {
        if(!channel.isPlaying()) {
            state = Idle;
        }
    }
}

void AudioPlayer::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void AudioPlayer::setVolume(double volume) {
    channel.setVolume(volume);
}

void AudioPlayer::setDistance(double distance) {
    channel.setDistance(distance);
}

bool operator ==(const AudioPlayer &ap0, const AudioPlayer &ap1) {
    return ap0.id == ap1.id;
}
