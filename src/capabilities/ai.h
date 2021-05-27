#ifndef AI_H
#define AI_H


#include "controller.h"
#include "docker.h"

#include <src/math/line2d.h>

#include <src/tasks/dockingtask.h>


class AI : public Controller {
public:

    AI();

    bool executeDocking(const e172::ptr<Unit>& targetUnit, e172::Context *context);


    // Entity interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // AI_H
