#include "audiosample.h"

namespace e172 {


AudioSample AudioSample::newAudioSample(e172::SharedContainer::data_ptr data, e172::SharedContainer::ptr id, e172::SharedContainer::destructor_t destructor)
{

    return newSharedContainer<AudioSample>(data,id,destructor);
}

AudioSample::AudioSample()
{

}

}
