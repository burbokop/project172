#ifndef AI_H
#define AI_H


#include "capabilities/controller.h"


class AI : public Controller {
public:
    AI();

    // Worker interface
public:
    void tick(Context *context, Event *event);
};

#endif // AI_H
