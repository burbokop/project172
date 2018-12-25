#include "event.h"


void Event::loop()
{
    while (!this->exitFlag) {
        SDL_Event event;
        if (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                this->exitFlag = true;
            }
            else if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.scancode == SDL_SCANCODE_F12) exitFlag = true;
                if(event.key.keysym.scancode == SDL_SCANCODE_F1 || event.key.keysym.scancode == SDL_SCANCODE_F2) pauseFlag = false;
                this->setKey(event.key.keysym.scancode, true);
            }
            else if(event.type == SDL_KEYUP) {
                if(event.key.keysym.scancode == SDL_SCANCODE_F2) pauseFlag = true;
                this->setKey(event.key.keysym.scancode, false);
            }
            else if(event.type == SDL_MOUSEMOTION) {
                this->mouse = Vector(event.motion.x, event.motion.y);
            }

            //this->handleEvent(&event);
        }
    }
}



Event::Event()
{
    this->exitFlag = false;
    this->pauseFlag = false;
    this->scancode = new bool[512];
}

void Event::run()
{
    this->thread = std::thread(&Event::loop, this);
}

void Event::quit()
{
    this->exitFlag = true;
    this->thread.join();
}



bool Event::getKey(int key)
{
    return this->scancode[key];
}

bool Event::getExitFlag()
{
    return this->exitFlag;
}

void Event::setKey(int key, bool value)
{
    if(key >= 0 && key < 512) {
        this->scancode[key] = value;
    } else {
        printf("setKey error: out of bound exeption");
    }
}
