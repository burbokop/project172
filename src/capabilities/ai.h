#ifndef AI_H
#define AI_H


#include "controller.h"


class AI : public Controller {
public:
    enum Status {
        DockingExecution,
        Idle
    };
private:
    e172::ptr<Unit> m_targetUnit;
    Status m_status;
public:

    AI();

    void executeDocking(const e172::ptr<Unit>& targetUnit);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler*);
    Status status() const;

    // Entity interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // AI_H
