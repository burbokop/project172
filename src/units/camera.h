#ifndef CAMERA_H
#define CAMERA_H


#include "movable.h"
#include <src/capabilities/controller.h>

#include <src/engine/graphics/abstractrenderer.h>


class Camera : public Movable {
    e172::AbstractRenderer::Camera r_cam;
    int m_i = 0;
protected:
    static const double STOP_DISTANCE;
    static const double MAX_SPEED_MULTIPLIER;

    Controller *target = nullptr;

public:
    Camera();
    Camera(Controller *target);
    void setTarget(Controller *target);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    // Unit interface
public:
    void hit(e172::Context *, int);
};

#endif // CAMERA_H
