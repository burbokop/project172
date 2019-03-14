#ifndef NEAR_H
#define NEAR_H

#include <vector>


#include "capabilities/controller.h"


class Near : public Object {
private:
    static const double RADIUS_DELTA;
    static const double DEFAULT_RADIUS;
    static const double WARP_RADIUS_MILTIPLIER;

    std::vector<Worker*> *origin = nullptr;
    std::vector<Worker*> *focus = nullptr;
    Controller *center = nullptr;
    unsigned int addingIterator = 0;
    unsigned int removingIterator = 0;

    double radius = 0;

    void remove();
    void add();

    double getLocalRadius(Unit *center);

public:


    Near(std::vector<Worker*> *origin, Controller *center, double radius = DEFAULT_RADIUS);
    void update();

    std::vector<Worker*> *getFocus();
};

#endif // NEAR_H
