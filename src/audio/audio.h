#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <string>




typedef Mix_Chunk AudioSample;

class Audio {
public:
    static const int MAX_MAPPED_VOLUME;
    static const int MAX_CHANNEL_COUNT = 512;

    static void init();
    static AudioSample *loadSample(std::string path);
};

#endif // AUDIO_H
