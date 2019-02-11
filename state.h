#ifndef STATE_H
#define STATE_H

#include "object.h"

class State : public Object {
    int maxFPS = 60;

public:
    State();


    int getMaxFPS() const;
    void setMaxFPS(int value);
};

#endif // STATE_H
