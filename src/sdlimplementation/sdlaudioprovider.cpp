#include "sdlaudioprovider.h"
#include "SDL2/SDL_mixer.h"


SDLAudioProvider::SDLAudioProvider()
{

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


e172::AudioChannel SDLAudioProvider::reserveChannel()
{
}
