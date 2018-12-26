#ifndef UNIT_H
#define UNIT_H

#include <iterator>
#include <algorithm>

#include "worker.h"
#include "additional/vector.h"
#include "capabilities/modulehandler.h"
#include "loadable.h"


class Unit : public Worker, public Loadable {
private:
    double angle = 0;
    double dstAngle = 0;
    bool angleLocked = false;

protected:
    static const double DEFAULT_ROTATION_SPEED;
    double getRotationSpeed();

    std::vector<Capability*> capabilities;


    Vector pos;


public:
    Unit();
    Unit(Loadable *tmp);


    void place(Vector pos, double angle);

    void addCapability(Capability *capability);
    void removeCapability(Capability *capability);

    ModuleHandler *getModuleHandler();

    void rotateLeft();
    void rotateRight();
    void lockAngle(double angle);
    void unlockAngle();

    Vector getPosition();
    double getAngle();


    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // UNIT_H
