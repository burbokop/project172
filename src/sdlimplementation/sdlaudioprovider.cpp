#include "sdlaudioprovider.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>

SDLAudioProvider::SDLAudioProvider() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
}


e172::AudioSample SDLAudioProvider::loadAudioSample(const std::string &path) {
    auto audio = Mix_LoadWAV(path.c_str());

    if (audio){
        auto handle = new e172::AudioSample::handle<Mix_Chunk *> (audio);
        return __newAudioSample(handle, this, [](e172::AudioSample::data_ptr handle){
            auto h = e172::AudioSample::handle_cast<Mix_Chunk*>(handle);
            Mix_FreeChunk(h->c);
            delete h;
        });
    }
    return e172::AudioSample();
}


e172::AudioChannel SDLAudioProvider::reserveChannel() {
    m_currentChannelCount++;
    if (m_currentChannelCount > m_reservedChannelCount){

        m_reservedChannelCount = Mix_AllocateChannels(m_reservedChannelCount + ReserveStep);
        if (m_currentChannelCount > m_reservedChannelCount){
            std::cout << "Audio channel can not be created, created: " << m_reservedChannelCount << " required : " << m_currentChannelCount << std::endl;

        }
    }
    int channel = 0;

    if (freeChannel.size() > 0){
        channel = freeChannel.front();
        freeChannel.pop();

    } else {

        channel = m_currentChannelCount - 1;
    }


    return __newAudioChannel(
                new e172::AudioChannel::handle<int>(channel),
                this,
                [this](e172::AudioChannel::data_ptr data){
        auto c = e172::AudioChannel::handle_cast<int>(data);
        Mix_Pause(c->c);
        freeChannel.push(c->c);
        delete c;
    },
    [](e172::AudioChannel::data_ptr data , double volume){
    auto c = e172::AudioChannel::handle_cast<int>(data);
    Mix_Volume(c->c, static_cast<int>(MIX_MAX_VOLUME*volume));
},
[](e172::AudioChannel::data_ptr data, const e172::AudioSample& sample, int loops){
    const auto c = e172::AudioChannel::handle_cast<int>(data);
    const auto s = audioSampleData<Mix_Chunk*>(sample);
    Mix_PlayChannelTimed(c->c, s, loops - 1, -1);
},
[](e172::AudioChannel::data_ptr data){
    auto c = e172::AudioChannel::handle_cast<int>(data);
    return Mix_Playing(c->c);

},
[](e172::AudioChannel::data_ptr data){
    auto c = e172::AudioChannel::handle_cast<int>(data);
    Mix_Pause(c->c);
}
);

}
