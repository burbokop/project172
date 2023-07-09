#pragma once

#include "../../informative.h"
#include <e172/entity.h>
#include <list>

namespace proj172::core {

class UnitsAmountInfo : public Informative
{
private:
    e172::Context *m_context = nullptr;
public:
    UnitsAmountInfo(e172::Context *context);

    // IInformative interface
public:
    std::string info() const override;
};

} // namespace proj172::core
