#ifndef FPSMONITOR_H
#define FPSMONITOR_H

#include <SDL2/SDL.h>
#include <engine/time/elapsedtimer.h>
#include <vector>

#include "iinformative.h"

class FPSMonitor : public IInformative {
private:
    Uint32 startclock = 0;
    Uint32 deltaclock = 0;
    Uint32 currentFPS = 0;
    Uint32 averageFPS = 0;

    std::vector<Uint32> fpsArray;
    e172::ElapsedTimer outputTimer = e172::ElapsedTimer(500);

    std::string title;

public:
    FPSMonitor(std::string title = "FPS:");
    void count();
    int operator* (int term);
    Uint32 toUint32();

    // IInformative interface
public:
    std::string getInfo();
};

#endif // FPSMONITOR_H
