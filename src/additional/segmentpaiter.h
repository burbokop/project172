#pragma once

#include <e172/entity.h>
#include <e172/math/physicalobject.h>
#include <e172/time/elapsedtimer.h>

namespace proj172::core {

class SegmentPainter : public e172::Entity, public e172::PhysicalObject
{
    e172::ElapsedTimer timer;
public:
    SegmentPainter(e172::FactoryMeta &&meta);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core
