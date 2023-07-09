#pragma once

#include "../capabilities/controller.h"
#include <e172/graphics/abstractrenderer.h>
#include <e172/math/physicalobject.h>

namespace proj172::core {

class Camera : public e172::Entity, public e172::PhysicalObject {
    e172::AbstractRenderer::Camera r_cam;
    int m_i = 0;
protected:
    static const double STOP_DISTANCE;
    static const double MAX_SPEED_MULTIPLIER;

    e172::ptr<Controller> m_target = nullptr;

public:
    Camera(e172::FactoryMeta &&meta, const e172::ptr<Controller> &target = nullptr);
    void setTarget(const e172::ptr<Controller>& target);
    e172::ptr<Controller> target() const;

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *) override;
    void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core
