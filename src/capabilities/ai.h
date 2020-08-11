#ifndef AI_H
#define AI_H


#include "capabilities/controller.h"


class AI : public Controller {
public:
    AI();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
};

#endif // AI_H
