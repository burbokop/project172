#ifndef SDLAUDIOPROVIDER_H
#define SDLAUDIOPROVIDER_H

#include "audio/abstractaudioprovider.h"

class SDLAudioProvider: public e172::AbstractAudioProvider
{
public:
    SDLAudioProvider();

    // AbstractAudioProvider interface
public:
    virtual e172::AudioSample loadAudioSample(const std::string &path) override;
    virtual e172::AudioChannel reserveChannel() override;
};

#endif // SDLAUDIOPROVIDER_H
