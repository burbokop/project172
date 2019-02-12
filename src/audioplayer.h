#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "worker.h"

#include <SDL2/SDL_mixer.h>

class AudioPlayer : public Worker {
public:
    static Uint8 NONE;
    static Uint8 START_PLAYING;
    static Uint8 LOOP_PLAYING;
    static Uint8 STOP_PLAYING;

private:
    int channel = -1;
    Uint8 state = NONE;
    bool playPressed = false;

    Mix_Chunk *startChunk = nullptr;
    Mix_Chunk *loopChunk = nullptr;
    Mix_Chunk *stopChunk = nullptr;


    static bool initialized;
    static void initAudio();
    static void checkInitialized();

public:
    AudioPlayer();
    AudioPlayer(Mix_Chunk *start, Mix_Chunk *loop = nullptr, Mix_Chunk *stop = nullptr);

    // Worker interface
public:
    void play();
    void stop();


    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // AUDIOPLAYER_H
