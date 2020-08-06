#include "loadable.h"



Loadable::Loadable() {
}

Loadable::Loadable(Loadable *tmp) {
    tmp->clone(this);
}

Loadable::Loadable(Json::Value root, Animator animator, AudioPlayer audioPlayer, Timer timer, e172::Vector offset) {
    this->root = root;
    this->animator = animator;
    this->audioPlayer = audioPlayer;
    this->timer = timer;
    this->attachOffset = offset;
}

Loadable::Loadable(const Loadable & object) {
    this->root = object.root;
    this->animator = object.animator;
    this->audioPlayer = object.audioPlayer;
    this->timer = object.timer;
    this->attachOffset = object.attachOffset;
}

std::string Loadable::getAssetClass() {
    Json::Value classValue = root.get("class", "undefined");
    if(classValue.isString()) {
        return classValue.asString();
    }
    return "undefined";
}

void Loadable::clone(Loadable *dst) {
    dst->root = root;
    dst->animator = animator;
    dst->audioPlayer = audioPlayer;
    dst->timer = timer;
    dst->attachOffset = attachOffset;
}

Loadable::~Loadable() {}
