#include "guiminimap.h"
#include "units/camera.h"
#include "units/projectile.h"
#include "additional/lightparticle.h"

#include <engine/abstracteventhandler.h>

GUIMiniMap::GUIMiniMap(std::list<Entity*> *units) {
    this->units = units;
}

void GUIMiniMap::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(context);
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
        for(Entity *worker : *units) {
            Unit *unit = dynamic_cast<Unit*>(worker);
            if(unit) {
                e172::Vector posOnMap = ((unit->getPosition() - renderer->cameraPosition()) / range * size.module()) + (size / 2);

                if(posOnMap.quarter() == e172::Vector::QUARTER_RIGHT_DOWN && (size - posOnMap).quarter() == e172::Vector::QUARTER_RIGHT_DOWN) {
                    if(unit->is<Projectile*>()) {
                        renderer->drawSquare(point1 + posOnMap, 1, SelectedColor);
                    } else if (unit->isNot<LightParticle*>()) {
                        if(unit->is<Camera*>()) {
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
