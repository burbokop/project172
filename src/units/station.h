#pragma once

#include "unit.h"

namespace proj172::core {

class Station : public Unit
{
public:
    Station(e172::FactoryMeta &&meta);
};

} // namespace proj172::core
