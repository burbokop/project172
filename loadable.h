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
    Vector offset;

public:
    Loadable();
    Loadable(Loadable *tmp);
    Loadable(Json::Value root, Animator animator = Animator(), AudioPlayer audioPlayer = AudioPlayer(), Timer timer = Timer(100), Vector offset = Vector());
    Loadable(const Loadable &object);

    std::string getAssetClass();

    void clone(Loadable *dst);
};

#endif // LOADABLE_H
