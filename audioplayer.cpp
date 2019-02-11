#include "audioplayer.h"

Uint8 AudioPlayer::NONE = 0;
Uint8 AudioPlayer::START_PLAYING = 1;
Uint8 AudioPlayer::LOOP_PLAYING = 2;
Uint8 AudioPlayer::STOP_PLAYING = 3;



AudioPlayer::AudioPlayer() {
}

AudioPlayer::AudioPlayer(Mix_Chunk *start, Mix_Chunk *loop, Mix_Chunk *stop) {
    this->startChunk = start;
    this->loopChunk = loop;
    this->stopChunk = stop;
}

#include <iostream>
void AudioPlayer::play() {
    playPressed = true;
    if(state == NONE) {
        channel = Mix_PlayChannel(channel, startChunk, 0);
        state = START_PLAYING;
    }
}

void AudioPlayer::stop() {
    channel = Mix_PlayChannel(channel, stopChunk, 0);
    state = NONE;
}

void AudioPlayer::loop(Context *context, Event *event) {
    if(!playPressed && state != NONE) stop();
    playPressed = false;

    if (state == START_PLAYING && !Mix_Playing(channel)) {
        if(loopChunk != nullptr) {
            channel = Mix_PlayChannel(channel, loopChunk, -1);
            state = LOOP_PLAYING;
        } else {
            state = NONE;
        }
    }
}

void AudioPlayer::render(Renderer *renderer) {

}
