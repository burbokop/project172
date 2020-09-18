#ifndef SEGMENTPAITER_H
#define SEGMENTPAITER_H

#include <src/engine/entity.h>
#include <src/engine/physicalobject.h>

#include <src/engine/time/elapsedtimer.h>



class SegmentPaiter : public e172::Entity, public e172::PhysicalObject {
    e172::ElapsedTimer timer;
public:
    SegmentPaiter();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // SEGMENTPAITER_H
