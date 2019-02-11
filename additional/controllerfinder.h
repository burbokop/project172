#ifndef PLAYER2FINDER_H
#define PLAYER2FINDER_H

#include "iinformative.h"
#include "../capabilities/player.h"

class ControllerFinder : public IInformative {

private:
    Controller *p1;
    Controller *p2;
public:
    ControllerFinder(Controller *p1, Controller *p2);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // PLAYER2FINDER_H
