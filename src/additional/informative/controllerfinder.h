#ifndef PLAYER2FINDER_H
#define PLAYER2FINDER_H

#include <src/iinformative.h>
#include <src/capabilities/controller.h>

class ControllerFinder : public IInformative {

private:
    Controller *p1 = nullptr;
    Controller *p2 = nullptr;
public:
    ControllerFinder(Controller *p1, Controller *p2);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // PLAYER2FINDER_H
