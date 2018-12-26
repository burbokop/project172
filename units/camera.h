#ifndef CAMERA_H
#define CAMERA_H

#include "movable.h"
#include "capabilities/controller.h"

class Camera : public Movable
{
protected:
    static const double STOP_DISTANCE;
    static const double MAX_SPEED_MULTIPLIER;

    Controller *target;

public:
    Camera();
    Camera(Controller *target);
    void setTarget(Controller *target);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // CAMERA_H
