#include "audio.h"

const int Audio::MAX_VOLUME = MIX_MAX_VOLUME;


void Audio::init() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
}

AudioSample *Audio::loadSample(std::string path) {
    return Mix_LoadWAV(path.c_str());
}
