#include "state.h"


const unsigned State::TIMER = 0;
const unsigned State::DELAY = 1;

unsigned State::loopBehaviour = TIMER;
int State::maxFPS = 60;


int State::getMaxFPS() {
    return maxFPS;
}
/*
void State::setMaxFPS(int value) {
    maxFPS = value;
}
*/

unsigned State::getLoopBehaviour() {
    return loopBehaviour;
}

void State::setLoopBehaviour(Variant value) {
    loopBehaviour = value.isUint32();
}

#include <iostream>
void State::incMaxFps() {
    maxFPS++;
    std::cout << "maxFPS: " << maxFPS << "\n";
}

void State::decMaxFps() {
    maxFPS--;
    std::cout << "maxFPS: " << maxFPS << "\n";
}


State::State() {

}
