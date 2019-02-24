#include "audiochannel.h"

const int AudioChannel::INFINITELY = -1;

int AudioChannel::channelsReserved = 0;


#include <iostream>
void AudioChannel::allocate() {
    Mix_AllocateChannels(200);
    ptr = channelsReserved++;
    //ptr = 0;
    std::cout << "channel: " << ptr << "\n";
}

AudioChannel::AudioChannel() {
}

AudioChannel AudioChannel::createChannel() {
    return AudioChannel();
}

bool AudioChannel::isAvailable() {
    return (ptr != -1);
}

void AudioChannel::volume(int volume) {
    volumeValue = volume;
}

void AudioChannel::play(AudioSample *sample, int loops) {
    if(deadChannel) {
        allocate();
        deadChannel = false;
    }
    if(isAvailable()) {
        Mix_Volume(ptr, volumeValue);
        if(volumeValue > 0 && sample != nullptr) {
            if(loops > 0) {
                Mix_PlayChannel(ptr, sample, loops - 1);
            } else if (loops == INFINITELY) {
                Mix_PlayChannel(ptr, sample, INFINITELY);
            }
        }
    }
}

bool AudioChannel::isPlaying() {
    if(isAvailable()) {
        return Mix_Playing(ptr);
    } else {
        return false;
    }
}

void AudioChannel::stop() {
    if(isAvailable()) {
        Mix_Pause(ptr);
    }
}

void AudioChannel::free() {
    //ptr = -1;
}

AudioChannel::~AudioChannel() {
    //this->free();
}
