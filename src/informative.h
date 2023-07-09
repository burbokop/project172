#pragma once

#include <string>

namespace proj172::core {

class Informative
{
public:
    virtual std::string info() const { return {}; }
    virtual ~Informative() = default;
};

} // namespace proj172::core
