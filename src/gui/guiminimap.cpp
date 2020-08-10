#include "guiminimap.h"
#include "units/camera.h"
#include "units/projectile.h"
#include "additional/lightparticle.h"

GUIMiniMap::GUIMiniMap(Controller *player, std::vector<Worker *> *units) : GUIElement (player) {
    this->units = units;
}

void GUIMiniMap::tick(Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(context);
    if(eventHandler->keySinglePressed(e172::ScancodeEQUALS) || eventHandler->keySinglePressed(e172::ScancodeKP_PLUS)) {
        range /= 2;
    }
    else if(eventHandler->keySinglePressed(e172::ScancodeMINUS) || eventHandler->keySinglePressed(e172::ScancodeKP_MINUS)) {
        range *= 2;
    }
}

void GUIMiniMap::render(e172::AbstractRenderer *renderer) {
    e172::Vector size = renderer->resolution() / sizeRelation;

    e172::Vector point2 = renderer->resolution() - e172::Vector(margin, margin);
    e172::Vector point1 = point2 - size;
    if(point1.quarter() == e172::Vector::QUARTER_RIGHT_DOWN) {
        renderer->drawRect(point1, point2, DEFAULT_COLOR);

        e172::Vector playerShipPosOnMap;
        for(Worker *worker : *units) {
            Unit *unit = dynamic_cast<Unit*>(worker);
            if(unit) {
                e172::Vector posOnMap = ((unit->getPosition() - renderer->cameraPosition()) / range * size.module()) + (size / 2);

                if(posOnMap.quarter() == e172::Vector::QUARTER_RIGHT_DOWN && (size - posOnMap).quarter() == e172::Vector::QUARTER_RIGHT_DOWN) {
                    if(unit->is<Projectile*>()) {
                        renderer->drawSquare(point1 + posOnMap, 1, SELECTED_COLOR);
                    } else if (unit->isNot<LightParticle*>()) {
                        if(unit->is<Camera*>()) {
                            renderer->drawLine(point1 + posOnMap, point1 + playerShipPosOnMap, SELECTED_COLOR);
                            renderer->drawCircle(point1 + posOnMap, 4, SELECTED_COLOR >> 8);
                        } else if(player && unit == player->parent()) {
                            playerShipPosOnMap = posOnMap;
                            renderer->drawCircle(point1 + posOnMap, 2, SELECTED_COLOR << 8);
                        } else {
                            renderer->drawCircle(point1 + posOnMap, 2, SELECTED_COLOR << 8);
                        }
                    }
                }
            }
        }
    }
}
