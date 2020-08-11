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
    static AudioChannel __newAudioChannel(
            AudioChannel::data_ptr data,
            AudioChannel::ptr id,
            AudioChannel::destructor_t destructor,
            AudioChannel::volume_setter_t volume_setter,
            AudioChannel::play_t play,
            AudioChannel::is_playing_t is_palying,
            AudioChannel::pause_t pause
            );
    template<typename T>
    static T audioSampleData(const AudioSample &sample) { return sample.casted_handle<T>()->c; }
    static AudioSample::ptr audioId(const AudioSample &sample);

public:
    AbstractAudioProvider();
    virtual AudioSample loadAudioSample(const std::string &path) = 0;
    virtual AudioChannel reserveChannel() = 0;
    virtual ~AbstractAudioProvider();
};
}
#endif // AUDIOPROVIDER_H
