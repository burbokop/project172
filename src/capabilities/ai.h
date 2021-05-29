#ifndef AI_H
#define AI_H


#include "controller.h"
#include "docker.h"

#include <src/math/line2d.h>

#include <src/tasks/dockingtask.h>


class AI : public Controller {
public:

    AI();

    // Entity interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // AI_H
