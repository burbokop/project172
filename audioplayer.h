#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "worker.h"



class AudioPlayer : public Worker
{
public:
    AudioPlayer();

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // AUDIOPLAYER_H
