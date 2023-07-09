#pragma once

#include "../tasks/dockingtask.h"
#include "controller.h"
#include <e172/math/line2d.h>

namespace proj172::core {

class AI : public Controller {
public:
    AI(e172::FactoryMeta &&meta)
        : Controller(std::move(meta))
    {}

    // Entity interface
public:
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core
