#ifndef PLAYER2FINDER_H
#define PLAYER2FINDER_H

#include <src/iinformative.h>
#include <src/capabilities/controller.h>

namespace proj172::core {

class ControllerFinder : public IInformative {

private:
    Controller *p1 = nullptr;
    Controller *p2 = nullptr;
public:
    ControllerFinder(Controller *p1, Controller *p2);

    // IInformative interface
public:
    std::string info() const override;
};

} // namespace proj172::core

#endif // PLAYER2FINDER_H
