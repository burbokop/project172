#ifndef UNIT_H
#define UNIT_H

#include <iterator>
#include <algorithm>


#include "capabilities/modulehandler.h"
#include "capabilities/docker.h"

class Unit : public Worker, public Loadable, public IInformative {
private:
    double angle = 0;
    double rotationSpeed = DEFAULT_ROTATION_SPEED;
    double dstAngle = 0;
    bool angleLocked = false;
    double health = 0;
    double explosiveRadius = 0;
    Animator animator;
protected:
    static const double DEFAULT_ROTATION_SPEED;
    static const double ANGLE_DELTA_MULTIPLIER;
    double getRotationSpeed();

    std::vector<Capability*> capabilities;


    e172::Vector pos;


public:
    Unit();

    void place(e172::Vector pos, double angle);

    void addCapability(Capability *capability);
    void removeCapability(Capability *capability);

    ModuleHandler *getModuleHandler();
    Docker *getDocker();


    void rotateLeft();
    void rotateRight();
    void lockAngle(double angle);
    void rotateToAngle(double angle);
    bool isOnAngle(double angle);
    void unlockAngle();


    e172::Vector getPosition();
    virtual e172::Vector getVelocity();
    double getAngle();

    virtual void hit(Context *context, int value);

    // Worker interface
    void tick(Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    ~Unit();

    // IInformative interface

    std::string getInfo();




    // Object interface

    std::string getType() const;
    void setRotationSpeed(double value);
};

#endif // UNIT_H
