#ifndef SDLAUDIOPROVIDER_H
#define SDLAUDIOPROVIDER_H
#include <queue>

#include <src/audio/abstractaudioprovider.h>

class SDLAudioProvider: public e172::AbstractAudioProvider {
    enum { ReserveStep = 10 };

    int m_reservedChannelCount = 0;
    int m_currentChannelCount = 0;
    std::queue<int> freeChannel;
public:
    SDLAudioProvider();

    // AbstractAudioProvider interface
public:
    virtual e172::AudioSample loadAudioSample(const std::string &path) override;
    virtual e172::AudioChannel reserveChannel() override;
};

#endif // SDLAUDIOPROVIDER_H
