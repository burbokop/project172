#include "fpsmonitor.h"

FPSMonitor::FPSMonitor(std::string title) {
    this->title = title;
}

void FPSMonitor::count() {
    deltaclock = SDL_GetTicks() - startclock;
    startclock = SDL_GetTicks();

    if ( deltaclock != 0 )
        currentFPS = 1000 / deltaclock;

    fpsArray.push_back(currentFPS);

    if(outputTimer.count(true)) {
        Uint32 sum = 0;
        Uint32 i = 0;
        for(Uint32 inst : fpsArray) {
            sum += inst;
            i++;
        }

        averageFPS = (i != 0) ? (sum / i) : sum;
        fpsArray.clear();
    }
}

int FPSMonitor::operator*(int term) {
    return static_cast<int>(currentFPS) * term;
}

Uint32 FPSMonitor::toUint32() {
    return currentFPS;
}

std::string FPSMonitor::getInfo() {
    return title + ' ' + std::to_string(averageFPS);
}
