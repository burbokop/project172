#include "audioplayer.h"
#include "units/camera.h"
#include <engine/math/math.h>

const unsigned AudioPlayer::NONE = 0;
const unsigned AudioPlayer::START_PLAYING = 1;
const unsigned AudioPlayer::LOOP_PLAYING = 2;
const unsigned AudioPlayer::STOP_PLAYING = 3;

const int AudioPlayer::CUT_VOLUME_DISTANCE = 1024;
const int AudioPlayer::FULL_VOLUME_DISTANCE = 128;



AudioPlayer::AudioPlayer(AudioSample *start, AudioSample *loop, AudioSample *stop) {
    this->startChunk = start;
    this->loopChunk = loop;
    this->stopChunk = stop;
    this->channel.free();
    this->channel = AudioChannel::createChannel();
}

AudioPlayer::~AudioPlayer() {
    stop();
}

void AudioPlayer::play() {
    if(state == NONE) {
        channel.play(startChunk, 1);
        state = START_PLAYING;
    }
}

void AudioPlayer::stop() {
    channel.play(stopChunk, 1);
    state = NONE;
}

void AudioPlayer::tick(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);

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

void AudioPlayer::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void AudioPlayer::setVolume(int volume) {
    channel.volume(volume);
}

void AudioPlayer::setVolumeByDistance(double distance) {
    int intDistance = static_cast<int>(distance);
    if(intDistance < FULL_VOLUME_DISTANCE) intDistance = FULL_VOLUME_DISTANCE;
    if(intDistance > CUT_VOLUME_DISTANCE) intDistance = CUT_VOLUME_DISTANCE;
    setVolume(e172::Math::map(intDistance, FULL_VOLUME_DISTANCE, CUT_VOLUME_DISTANCE, Audio::MAX_VOLUME, 0));
}

bool operator ==(const AudioPlayer &ap0, const AudioPlayer &ap1) {
    return ap0.id == ap1.id;
}
