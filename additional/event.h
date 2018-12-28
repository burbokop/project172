#ifndef EVENT_H
#define EVENT_H

#include <thread>
#include <SDL2/SDL.h>

#include "additional/vector.h"


class Event
{
private:
    bool exitFlag;
    bool pauseFlag;
    Vector mouse;
    bool *scancode;
    bool *pressed;
    std::thread thread;

    void loop();
    void setKey(int key, bool value);
    void setPresed(int key, bool value);
public:
    Event();
    void run();
    void quit();
    bool getKey(int key);
    bool getPressed(int key);

    bool getExitFlag();
};
#endif // EVENT_H
