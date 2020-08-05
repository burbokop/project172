#ifndef EVENT_H
#define EVENT_H

#include <thread>
#include <SDL2/SDL.h>


#include <src/engine/math/vector.h>

class Event {
private:
    bool exitFlag = false;
    bool pauseFlag = false;
    e172::Vector mouse;
    const int bufferSize = 512;
    bool *scancode = new bool[bufferSize];
    bool *pressed = new bool[bufferSize];

    std::thread *thread = nullptr;

    void handleEvent(SDL_Event event);
    void threadFunction();
    void setKey(int key, bool value);
    void setPresed(int key, bool value);

public:
    Event();
    void runInNewThread();

    void loop();

    void quit();
    bool getKey(int key);
    bool getPressed(int key);

    bool getExitFlag();

    void unpressAll();
};
#endif // EVENT_H
