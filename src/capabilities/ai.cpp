#include "ai.h"
#include "warestorage.h"

#include <src/graphics/abstractrenderer.h>
#include <src/units/ship.h>
#include <src/units/unit.h>
#include <e172/src/math/math.h>
#include <src/debug.h>
#include <src/math/line2d.h>
#include <src/math/math.h>
#include <iostream>


AI::AI() : Controller () {}

bool AI::executeDocking(const e172::ptr<Unit> &targetUnit) {
    return dockingTaskExecutor.start(targetUnit);
}

void AI::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    dockingTaskExecutor.proceed(context);
}


void AI::render(e172::AbstractRenderer *renderer) {
    if(dockingTaskExecutor.status() != DockingTaskExecutor::Idle && dockingTaskExecutor.status() != DockingTaskExecutor::Docked) {
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignTop, 10);
        renderer->drawStringShifted(dockingTaskExecutor.statusString(), parentUnit()->position() + e172::Vector(0, -32), 0xffaaaa, format);
        renderer->drawLineShifted(dockingTaskExecutor.landingStrip(), 0xffaaff);
        renderer->drawCircleShifted(dockingTaskExecutor.targetPoint(), 4, 0xffaaff);
    }    
}
