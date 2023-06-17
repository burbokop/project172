#pragma once

#include "controller.h"
#include <src/math/line2d.h>
#include <src/tasks/dockingtask.h>

namespace proj172::core {

class AI : public Controller {
public:
    AI(e172::FactoryMeta &&meta)
        : Controller(std::move(meta))
    {}

    // Entity interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core
