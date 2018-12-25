#include "loadable.h"


Loadable::Loadable() {
}

Loadable::Loadable(Loadable *tmp) {
    tmp->clone(this);
}

Loadable::Loadable(Json::Value root, Animator animator, AudioPlayer audioPlayer, Timer timer) {
    this->root = root;
    this->animator = animator;
    this->audioPlayer = audioPlayer;
    this->timer = timer;
}

#include <iostream>
Loadable::Loadable(const Loadable & object) {
    std::cout << "copy\n";
    this->root = object.root;
    this->animator = object.animator;
    this->audioPlayer = object.audioPlayer;
    this->timer = object.timer;
}

std::string Loadable::getClass() {
    std::cout << "f1\n";

    for(Json::Value v : root) {
        if(v.isString()) std::cout << "v: " << v.asString() << "\n";
    }
    std::cout << "f2.1\n";

    Json::Value classValue = root.get("class", "def");
    std::cout << "f2\n";

    if(classValue.isString()) {
        std::cout << "f3\n";

        return classValue.asString();
    }
    return "undefined";
}

void Loadable::clone(Loadable *dst) {
    std::cout << "clone\n";
    dst->root = root;
    dst->animator = animator;
    dst->audioPlayer = audioPlayer;
    dst->timer = timer;
}
