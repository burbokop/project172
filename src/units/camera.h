#ifndef CAMERA_H
#define CAMERA_H


#include "movable.h"
#include <src/capabilities/controller.h>

#include <src/engine/graphics/abstractrenderer.h>


class Camera : public e172::Entity, public e172::PhysicalObject {
    e172::AbstractRenderer::Camera r_cam;
    int m_i = 0;
protected:
    static const double STOP_DISTANCE;
    static const double MAX_SPEED_MULTIPLIER;

    Controller *m_target = nullptr;

public:
    Camera(Controller *target = nullptr);
    void setTarget(Controller *target);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *renderer);

    // Unit interface
public:
    void hit(e172::Context *, int);
    Controller *target() const;
};

#endif // CAMERA_H
