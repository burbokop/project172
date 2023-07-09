#pragma once

#include "../../capabilities/controller.h"
#include "../../informative.h"

namespace proj172::core {

class ControllerFinder : public Informative
{
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

