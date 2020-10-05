#include "abstractaudioprovider.h"

namespace e172 {


double AbstractAudioProvider::generalVolume() const
{
    return m_generalVolume;
}

void AbstractAudioProvider::setGeneralVolume(double generalVolume)
{
    m_generalVolume = generalVolume;
}

AudioSample AbstractAudioProvider::__newAudioSample(AudioSample::data_ptr data, AudioSample::ptr id, AudioSample::destructor_t destructor) {
    return AudioSample::newAudioSample(data, id, destructor);
}

AudioChannel AbstractAudioProvider::__newAudioChannel(
        AudioChannel::data_ptr data,
        AudioChannel::ptr id,
        AudioChannel::destructor_t destructor,
        AudioChannel::volume_setter_t volume_setter,
        AudioChannel::play_t play,
        AudioChannel::is_playing_t is_palying,
        AudioChannel::pause_t pause) {
    return AudioChannel::newAudioChannel(data, id, destructor, volume_setter, play, is_palying, pause);
}

AbstractAudioProvider::AbstractAudioProvider()
{

}

AbstractAudioProvider::~AbstractAudioProvider() {}

}
