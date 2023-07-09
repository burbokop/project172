#include "guiminimap.h"

#include "../additional/lightparticle.h"
#include "../units/camera.h"
#include "../units/projectile.h"
#include <e172/abstracteventprovider.h>
#include <e172/context.h>
#include <e172/eventhandler.h>

namespace proj172::core {

void GUIMiniMap::proceed(e172::Context *context, e172::EventHandler *eventHandler)
{
    if (eventHandler->keySinglePressed(e172::ScancodeEquals)
        || eventHandler->keySinglePressed(e172::ScancodeKpPlus)) {
        m_range /= 2;
    } else if (eventHandler->keySinglePressed(e172::ScancodeMinus)
               || eventHandler->keySinglePressed(e172::ScancodeKpMinus)) {
        m_range *= 2;
    }
}

void GUIMiniMap::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    e172::Vector size = renderer->resolution() / m_sizeRelation;

    e172::Vector point2 = renderer->resolution() - e172::Vector<double>(margin(), margin());
    e172::Vector point1 = point2 - size;
    if (point1.quarter() == e172::Vector<double>::Quarter::RightBottom) {
        renderer->drawRect(point1, point2, DefaultColor);

        e172::Vector<double> playerShipPosOnMap;
        for (const auto &entity : context->entities()) {
            const auto unit = e172::smart_cast<Unit>(entity);
            if(unit) {
                e172::Vector posOnMap = ((unit->position() - renderer->cameraPosition()) / m_range
                                         * size.module())
                                        + (size / 2);

                if (posOnMap.quarter() == e172::Vector<double>::Quarter::RightBottom
                    && (size - posOnMap).quarter() == e172::Vector<double>::Quarter::RightBottom) {
                    if(unit->instanceOf<Projectile>()) {
                        renderer->drawSquare(point1 + posOnMap, 1, SelectedColor);
                    } else if (!unit->instanceOf<LightParticle>()) {
                        if(unit->instanceOf<Camera>()) {
                            renderer->drawLine(point1 + posOnMap, point1 + playerShipPosOnMap, SelectedColor);
                            renderer->drawCircle(point1 + posOnMap, 4, SelectedColor >> 8);
                        } else if(controller() && unit == controller()->parentUnit()) {
                            playerShipPosOnMap = posOnMap;
                            renderer->drawCircle(point1 + posOnMap, 2, SelectedColor << 8);
                        } else {
                            renderer->drawCircle(point1 + posOnMap, 2, SelectedColor << 8);
                        }
                    }
                }
            }
        }
    }
}

} // namespace proj172::core
