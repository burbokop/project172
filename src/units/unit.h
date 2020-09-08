#ifndef UNIT_H
#define UNIT_H

#include <iterator>
#include <algorithm>


#include <src/capabilities/modulehandler.h>
#include <src/capabilities/docker.h>

class Unit : public e172::Entity, public e172::Loadable, public IInformative {
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


    void rotateLeft(e172::Context *context);
    void rotateRight(e172::Context *context);
    void lockAngle(double angle);
    void rotateToAngle(e172::Context *context, double angle);
    bool isOnAngle(e172::Context *context, double angle);
    void unlockAngle();


    e172::Vector position();
    virtual e172::Vector velocity();
    double getAngle();

    virtual void hit(e172::Context *context, int value);

    // Entity interface
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    ~Unit();

    // IInformative interface

    std::string getInfo();


    void setRotationSpeed(double value);
};

#endif // UNIT_H
