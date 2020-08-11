#ifndef AUDIOSAMPLE_H
#define AUDIOSAMPLE_H

#include <engine/sharedcontainer.h>

namespace e172 {


class AudioSample : public e172::SharedContainer
{
    friend class AbstractAudioProvider;
    static AudioSample newAudioSample(data_ptr data, ptr id, destructor_t destructor);

public:
    AudioSample();
};

}
#endif // AUDIOSAMPLE_H
