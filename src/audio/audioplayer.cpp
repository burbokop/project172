#include "audioplayer.h"
#include "units/camera.h"
#include "additional/math.h"


Uint8 AudioPlayer::NONE = 0;
Uint8 AudioPlayer::START_PLAYING = 1;
Uint8 AudioPlayer::LOOP_PLAYING = 2;
Uint8 AudioPlayer::STOP_PLAYING = 3;

int AudioPlayer::CUT_VOLUME_DISTANCE = 1024;
int AudioPlayer::FULL_VOLUME_DISTANCE = 128;



AudioPlayer::AudioPlayer(AudioSample *start, AudioSample *loop, AudioSample *stop) {
    this->startChunk = start;
    this->loopChunk = loop;
    this->stopChunk = stop;
    this->channel.free();
    this->channel = AudioChannel::createChannel();
}

void AudioPlayer::play() {
    playPressed = true;
    if(state == NONE) {
        channel.play(startChunk, 1);
        state = START_PLAYING;
    }
}

void AudioPlayer::stop() {
    channel.play(stopChunk, 1);
    state = NONE;
}

void AudioPlayer::loop(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);
    if(!playPressed && state != NONE) stop();
    playPressed = false;

    if(state == START_PLAYING && !channel.isPlaying()) {
        if(loopChunk != nullptr) {
            channel.play(loopChunk, AudioChannel::INFINITELY);
            state = LOOP_PLAYING;
        } else {
            state = NONE;
        }
    }
    if(state == NONE) channel.free();
}

void AudioPlayer::render(Renderer *renderer) {
    UNUSED(renderer);
}

void AudioPlayer::setVolume(int volume) {
    channel.volume(volume);
}

void AudioPlayer::setVolumeByDistance(double distance) {
    int intDistance = static_cast<int>(distance);
    if(intDistance < FULL_VOLUME_DISTANCE) intDistance = FULL_VOLUME_DISTANCE;
    if(intDistance > CUT_VOLUME_DISTANCE) intDistance = CUT_VOLUME_DISTANCE;
    setVolume(Math::map(intDistance, FULL_VOLUME_DISTANCE, CUT_VOLUME_DISTANCE, Audio::MAX_VOLUME, 0));
}
