#ifndef AUDIOPROVIDER_H
#define AUDIOPROVIDER_H

#include "audiochannel.h"
#include "audiosample.h"

#include <string>
namespace e172 {
class AbstractAudioProvider
{
protected:
    static AudioSample __newAudioSample(AudioSample::data_ptr data, AudioSample::ptr id, AudioSample::destructor_t destructor);
public:
    AbstractAudioProvider();
    virtual AudioSample loadAudioSample(const std::string &path) = 0;
    virtual AudioChannel reserveChannel() = 0;
    virtual ~AbstractAudioProvider();
};
}
#endif // AUDIOPROVIDER_H
