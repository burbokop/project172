#ifndef UNIT_H
#define UNIT_H

#include <iterator>
#include <algorithm>


#include "capabilities/modulehandler.h"


class Unit : public Worker, public Loadable, public IInformative {
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

    virtual void hit(Context *context, int value);

    // Worker interface
public:
    void loop(Context *context, Event *event);
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
