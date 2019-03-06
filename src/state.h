#ifndef STATE_H
#define STATE_H


#include "additional/variant.h"


class State : public Object {
public:
    static const unsigned TIMER;
    static const unsigned DELAY;

private:

    static int maxFPS;
    static unsigned loopBehaviour;

public:
    State();

    static int getMaxFPS();
    //static void setMaxFPS(int value);
    static unsigned getLoopBehaviour();
    static void setLoopBehaviour(Variant value);

    static void incMaxFps();
    static void decMaxFps();
};

#endif // STATE_H
