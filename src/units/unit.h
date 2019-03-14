#ifndef UNIT_H
#define UNIT_H

#include <iterator>
#include <algorithm>


#include "capabilities/modulehandler.h"
#include "capabilities/docker.h"

class Unit : public Worker, public Loadable, public IInformative {
private:
    double angle = 0;
    double dstAngle = 0;
    bool angleLocked = false;

protected:
    static const double DEFAULT_ROTATION_SPEED;
    static const double ANGLE_DELTA_MULTIPLIER;
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
    Docker *getDocker();


    void rotateLeft();
    void rotateRight();
    void lockAngle(double angle);
    void rotateToAngle(double angle);
    bool isOnAngle(double angle);
    void unlockAngle();


    Vector getPosition();
    virtual Vector getVelocity();
    double getAngle();

    virtual void hit(Context *context, int value);

    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(Renderer *renderer);

    ~Unit();

    // IInformative interface
public:
    std::string getInfo();




    // Object interface
public:
    std::string getType() const;
};

#endif // UNIT_H
