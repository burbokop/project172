#include "state.h"


const uint8_t State::TIMER = 0;
const uint8_t State::DELAY = 1;

uint8_t State::loopBehaviour = TIMER;


int State::getMaxFPS() const {
    return maxFPS;
}

void State::setMaxFPS(int value)
{
    maxFPS = value;
}

uint8_t State::getLoopBehaviour() {
    return loopBehaviour;
}

void State::setLoopBehaviour(Auto value) {
    loopBehaviour = value.isUint32();
}

State::State()
{

}
