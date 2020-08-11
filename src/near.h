#ifndef NEAR_H
#define NEAR_H

#include <vector>


#include "capabilities/controller.h"


class Near : public Object {
private:
    static const double RADIUS_DELTA;
    static const double DEFAULT_RADIUS;
    static const double WARP_RADIUS_MILTIPLIER;

    std::list<e172::Entity*> *origin = nullptr;
    std::list<e172::Entity*> *focus = nullptr;
    Controller *center = nullptr;

    std::list<e172::Entity*>::iterator addingIterator;
    std::list<e172::Entity*>::iterator removingIterator;

    double radius = 0;

    void remove();
    void add();

    double getLocalRadius(Unit *center);

public:


    Near(std::list<e172::Entity*> *origin, Controller *center, double radius = DEFAULT_RADIUS);
    void update();

    std::list<e172::Entity*> *entitiesInFocus();
};

#endif // NEAR_H
