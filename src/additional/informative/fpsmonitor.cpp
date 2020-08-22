#include "fpsmonitor.h"

#include <engine/time/time.h>



FPSMonitor::FPSMonitor(std::string title) {
    this->title = title;
}

void FPSMonitor::count() {
    const auto cms = e172::Time::currentMilliseconds();

    deltaclock = cms - startclock;
    startclock = cms;

    if ( deltaclock != 0 )
        currentFPS = 1000 / deltaclock;

    fpsArray.push_back(currentFPS);

    if(outputTimer.check()) {
        uint32_t sum = 0;
        uint32_t i = 0;
        for(uint32_t inst : fpsArray) {
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

uint32_t FPSMonitor::toUint32() {
    return currentFPS;
}

std::string FPSMonitor::getInfo() {
    return title + ' ' + std::to_string(averageFPS);
}
