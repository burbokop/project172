#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "units/movable.h"

class Projectile : public Movable {
public:
    Projectile();
    Projectile(Loadable *tmp);




    // Worker interface
public:
    void loop(std::vector<Worker *> *others, Event *event);
};

#endif // PROJECTILE_H
