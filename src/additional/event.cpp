#include "event.h"

void Event::handleEvent(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        this->exitFlag = true;
    } else if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.scancode == SDL_SCANCODE_F12) exitFlag = true;
        if(event.key.keysym.scancode == SDL_SCANCODE_F1 || event.key.keysym.scancode == SDL_SCANCODE_F2) pauseFlag = false;
        this->setKey(event.key.keysym.scancode, true);
        this->setPresed(event.key.keysym.scancode, true);
        //printf("e %i\n", event.key.keysym.scancode);
    } else if(event.type == SDL_KEYUP) {
        if(event.key.keysym.scancode == SDL_SCANCODE_F2) pauseFlag = true;
        this->setKey(event.key.keysym.scancode, false);
    } else if(event.type == SDL_MOUSEMOTION) {
        this->mouse = Vector(event.motion.x, event.motion.y);
    }
}

void Event::threadFunction() {
    while (!this->exitFlag) {
        SDL_Event event;
        if (SDL_WaitEvent(&event)) {
            handleEvent(event);
        }
    }
}

void Event::loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        handleEvent(event);
    }
}

Event::Event() {
    this->exitFlag = false;
    this->pauseFlag = false;
    this->scancode = new bool[512];
    this->pressed = new bool[512];

    for(unsigned int i = 0; i < 512; i++) {
        scancode[i] = false;
        pressed[i] = false;
    }
}

void Event::runInNewThread() {
    thread = new std::thread(&Event::loop, this);
}

void Event::quit() {
    this->exitFlag = true;
    if(thread != nullptr) {
        thread->join();
    }
}



bool Event::getKey(int key) {
    return this->scancode[key];
}

bool Event::getPressed(int key) {
    if(this->pressed[key]) {
        setPresed(key, false);
        return true;
    }
    return false;
}

bool Event::getExitFlag() {
    return this->exitFlag;
}

void Event::setKey(int key, bool value) {
    if(key >= 0 && key < 512) {
        this->scancode[key] = value;
    } else {
        printf("setKey error: out of bound exeption");
    }
}

void Event::setPresed(int key, bool value) {
    if(key >= 0 && key < 512) {
        this->pressed[key] = value;
    } else {
        printf("setKey error: out of bound exeption");
    }
}
