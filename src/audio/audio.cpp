#include "audio.h"

const int Audio::MAX_MAPPED_VOLUME = MIX_MAX_VOLUME;


void Audio::init() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    Mix_AllocateChannels(MAX_CHANNEL_COUNT);
}

AudioSample *Audio::loadSample(std::string path) {
    return Mix_LoadWAV(path.c_str());
}
