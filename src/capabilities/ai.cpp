#include "ai.h"
#include "warestorage.h"

#include <src/graphics/abstractrenderer.h>
#include <src/units/ship.h>
#include <src/units/unit.h>
#include <e172/src/math/math.h>
#include <src/debug.h>
#include <src/math/line2d.h>
#include <src/math/math.h>

namespace proj172::core {

void AI::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    /*
    if(dockingTask.status() != DockingTask::Idle && dockingTask.status() != DockingTask::Docked) {
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignTop, 10);
        renderer->drawStringShifted(dockingTask.statusString(), parentUnit()->position() + e172::Vector(0, -32), 0xffaaaa, format);
        renderer->drawLineShifted(dockingTask.landingStrip(), 0xffaaff);
        renderer->drawCircleShifted(dockingTask.targetPoint(), 4, 0xffaaff);
    }
    */
}

} // namespace proj172::core
