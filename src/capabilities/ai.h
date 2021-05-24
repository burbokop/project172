#ifndef AI_H
#define AI_H


#include "controller.h"
#include "docker.h"

#include <src/math/line2d.h>

#include <src/taskexecutors/dockingtaskexecutor.h>


class AI : public Controller {
    DockingTaskExecutor dockingTaskExecutor = DockingTaskExecutor(this);
public:

    AI();

    bool executeDocking(const e172::ptr<Unit>& targetUnit);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler*);

    // Entity interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // AI_H
