#include "guiminimap.h"

#include <src/units/camera.h>
#include <src/units/projectile.h>
#include <src/additional/lightparticle.h>

#include <src/engine/abstracteventhandler.h>
#include <src/engine/context.h>

GUIMiniMap::GUIMiniMap() {}

void GUIMiniMap::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    m_entities = context->entities();

    if(eventHandler->keySinglePressed(e172::ScancodeEquals) || eventHandler->keySinglePressed(e172::ScancodeKpPlus)) {
        range /= 2;
    }
    else if(eventHandler->keySinglePressed(e172::ScancodeMinus) || eventHandler->keySinglePressed(e172::ScancodeKpMinus)) {
        range *= 2;
    }
}

void GUIMiniMap::render(e172::AbstractRenderer *renderer) {
    e172::Vector size = renderer->resolution() / sizeRelation;

    e172::Vector point2 = renderer->resolution() - e172::Vector(margin(), margin());
    e172::Vector point1 = point2 - size;
    if(point1.quarter() == e172::Vector::QUARTER_RIGHT_DOWN) {
        renderer->drawRect(point1, point2, DefaultColor);

        e172::Vector playerShipPosOnMap;
        for(const auto& entity : m_entities) {
            const auto unit = e172::smart_cast<Unit>(entity);
            if(unit) {
                e172::Vector posOnMap = ((unit->position() - renderer->cameraPosition()) / range * size.module()) + (size / 2);

                if(posOnMap.quarter() == e172::Vector::QUARTER_RIGHT_DOWN && (size - posOnMap).quarter() == e172::Vector::QUARTER_RIGHT_DOWN) {
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
