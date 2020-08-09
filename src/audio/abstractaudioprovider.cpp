#include "abstractaudioprovider.h"

namespace e172 {


AudioSample AbstractAudioProvider::__newAudioSample(AudioSample::data_ptr data, AudioSample::ptr id, AudioSample::destructor_t destructor) {
    return AudioSample::newAudioSample(data, id, destructor);
}

AbstractAudioProvider::AbstractAudioProvider()
{

}

AbstractAudioProvider::~AbstractAudioProvider() {}

}
