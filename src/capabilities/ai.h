#ifndef AI_H
#define AI_H


#include "controller.h"
#include "docker.h"

#include <src/math/line2d.h>


class AI : public Controller {
public:
    enum Status {
        DockingExecution,
        Idle
    };
private:
    e172::ptr<Unit> m_targetUnit;
    Status m_status;
    std::string statusString;
    e172::ptr<Docker> docker = nullptr;
    e172::ptr<DockingSession> session = nullptr;

    e172::Line2d _line;
    double __ = 0;
    e172::Vector _vec;
    double _dist = 0;
public:

    AI();

    bool executeDocking(const e172::ptr<Unit>& targetUnit);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler*);
    Status status() const;

    // Entity interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // AI_H
