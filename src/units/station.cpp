#include "station.h"

namespace proj172::core {

Station::Station(e172::FactoryMeta &&meta)
    : Unit(std::move(meta))
{}

} // namespace proj172::core
