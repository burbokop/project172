#ifndef SEGMENTPAITER_H
#define SEGMENTPAITER_H

#include <src/entity.h>
#include <src/math/physicalobject.h>

#include <src/time/elapsedtimer.h>



class SegmentPaiter : public e172::Entity, public e172::PhysicalObject {
    e172::ElapsedTimer timer;
public:
    SegmentPaiter(e172::FactoryMeta &&meta);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // SEGMENTPAITER_H
