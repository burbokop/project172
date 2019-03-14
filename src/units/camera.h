#ifndef CAMERA_H
#define CAMERA_H


#include "units/movable.h"
#include "capabilities/controller.h"


class Camera : public Movable {
protected:
    static const double STOP_DISTANCE;
    static const double MAX_SPEED_MULTIPLIER;

    Controller *target = nullptr;

public:
    Camera();
    Camera(Controller *target);
    void setTarget(Controller *target);

    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(Renderer *renderer);

    // Unit interface
public:
    void hit(Context *context, int value);
};

#endif // CAMERA_H
