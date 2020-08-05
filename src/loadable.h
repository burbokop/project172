#ifndef LOADABLE_H
#define LOADABLE_H


#include "json/json.h"
#include "animator.h"
#include "time/timer.h"
#include "audio/audioplayer.h"


class Loadable {
protected:
    Json::Value root;
    Animator animator;
    AudioPlayer audioPlayer;
    Timer timer = Timer(100);
    e172::Vector attachOffset;

public:
    Loadable();
    Loadable(Loadable *tmp);
    Loadable(Json::Value root, Animator animator = Animator(), AudioPlayer audioPlayer = AudioPlayer(), Timer timer = Timer(100), e172::Vector offset = e172::Vector());
    Loadable(const Loadable &object);

    std::string getAssetClass();

    void clone(Loadable *dst);

    virtual ~Loadable();
};

#endif // LOADABLE_H
