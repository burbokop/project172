#ifndef STATE_H
#define STATE_H


#include "additional/auto.h"


class State : public Object {
public:
    static const uint8_t TIMER;
    static const uint8_t DELAY;


private:

    int maxFPS = 60;
    static uint8_t loopBehaviour;

public:
    State();

    int getMaxFPS() const;
    void setMaxFPS(int value);
    static uint8_t getLoopBehaviour();
    static void setLoopBehaviour(Auto value);
};

#endif // STATE_H
