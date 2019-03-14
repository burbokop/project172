#ifndef FPSMONITOR_H
#define FPSMONITOR_H

#include <SDL2/SDL.h>
#include <vector>

#include "iinformative.h"
#include "time/timer.h"


class FPSMonitor : public IInformative {
private:
    Uint32 startclock = 0;
    Uint32 deltaclock = 0;
    Uint32 currentFPS = 0;
    Uint32 averageFPS = 0;

    std::vector<Uint32> fpsArray;
    Timer outputTimer = Timer(500);

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
