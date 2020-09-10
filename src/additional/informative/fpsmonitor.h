#ifndef FPSMONITOR_H
#define FPSMONITOR_H

#include <src/engine/time/elapsedtimer.h>
#include <vector>

#include <src/iinformative.h>

class FPSMonitor : public IInformative {
private:
    uint32_t startclock = 0;
    uint32_t deltaclock = 0;
    uint32_t currentFPS = 0;
    uint32_t averageFPS = 0;

    std::vector<uint32_t> fpsArray;
    e172::ElapsedTimer outputTimer = e172::ElapsedTimer(500);

    std::string title;

public:
    FPSMonitor(std::string title = "FPS:");
    void count();
    int operator* (int term);
    uint32_t toUint32();

    // IInformative interface
public:
    std::string info() const override;
};

#endif // FPSMONITOR_H
