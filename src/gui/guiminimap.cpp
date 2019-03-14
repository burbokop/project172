#include "guiminimap.h"
#include "units/camera.h"
#include "units/projectile.h"
#include "additional/lightparticle.h"

GUIMiniMap::GUIMiniMap(Controller *player, std::vector<Worker *> *units) : GUIElement (player) {
    this->units = units;
}

void GUIMiniMap::tick(Context *context, Event *event) {
    UNUSED(context);
    if(event->getPressed(SDL_SCANCODE_EQUALS) || event->getPressed(SDL_SCANCODE_KP_PLUS)) {
        range /= 2;
    }
    else if(event->getPressed(SDL_SCANCODE_MINUS) || event->getPressed(SDL_SCANCODE_KP_MINUS)) {
        range *= 2;
    }
}

void GUIMiniMap::render(Renderer *renderer) {
    Vector size = renderer->getResolution() / sizeRelation;

    Vector point2 = renderer->getResolution() - Vector(margin, margin);
    Vector point1 = point2 - size;
    if(point1.quarter() == Vector::QUARTER_RIGHT_DOWN) {
        renderer->rect(point1, point2, DEFAULT_COLOR);

        Vector playerShipPosOnMap;
        for(Worker *worker : *units) {
            Unit *unit = dynamic_cast<Unit*>(worker);
            if(unit) {
                Vector posOnMap = ((unit->getPosition() - renderer->getCamera()->getPosition()) / range * size.module()) + (size / 2);

                if(posOnMap.quarter() == Vector::QUARTER_RIGHT_DOWN && (size - posOnMap).quarter() == Vector::QUARTER_RIGHT_DOWN) {
                    if(unit->is<Projectile*>()) {
                        renderer->square(point1 + posOnMap, 1, SELECTED_COLOR);
                    } else if (unit->isNot<LightParticle*>()) {
                        if(unit->is<Camera*>()) {
                            renderer->line(point1 + posOnMap, point1 + playerShipPosOnMap, SELECTED_COLOR);
                            renderer->circle(point1 + posOnMap, 4, SELECTED_COLOR >> 8);
                        } else if(player && unit == player->getParent()) {
                            playerShipPosOnMap = posOnMap;
                            renderer->circle(point1 + posOnMap, 2, SELECTED_COLOR << 8);
                        } else {
                            renderer->circle(point1 + posOnMap, 2, SELECTED_COLOR << 8);
                        }
                    }
                }
            }
        }
    }
}
