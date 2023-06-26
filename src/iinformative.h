#pragma once

#include <string>

namespace proj172::core {

class Informative
{
public:
    std::string virtual info() const;
    virtual ~Informative() = default;
};

} // namespace proj172::core
