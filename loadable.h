#ifndef LOADABLE_H
#define LOADABLE_H

#include "animator.h"
#include "audioplayer.h"
#include "jsoncpp/json/json.h"

class Loadable
{
protected:
    Json::Value root;
    Animator animator;
    AudioPlayer audioPlayer;
    Timer timer = Timer(100);

public:
    Loadable();
    Loadable(Loadable *tmp);
    Loadable(Json::Value root, Animator animator = Animator(), AudioPlayer audioPlayer = AudioPlayer(), Timer timer = Timer(100));
    Loadable(const Loadable &object);

    std::string getClass();

    void clone(Loadable *dst);
};

#endif // LOADABLE_H
