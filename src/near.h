#ifndef NEAR_H
#define NEAR_H

#include <vector>

#include "capabilities/controller.h"


class Near : public Object {
private:
    static const double RADIUS_DELTA;

    std::vector<Worker *> *origin = nullptr;
    std::vector<Worker *> *focus = nullptr;
    Controller *center = nullptr;
    unsigned int addingIterator = 0;
    unsigned int removingIterator = 0;

    double radius = 0;

    void add();
    void remove();


public:
    Near(std::vector<Worker *> *origin, Controller *center, double radius);
    void update();
    std::vector<Worker *> *getFocus();
};

#endif // NEAR_H
