#include "guiminimap.h"
#include "units/camera.h"
#include "units/projectile.h"
#include "additional/lightparticle.h"

GUIMiniMap::GUIMiniMap(Controller *player, std::vector<Worker *> *units) : GUIElement (player) {
    this->units = units;
}

std::string GUIMiniMap::getTitle() {
    return "[no title]";
}

void GUIMiniMap::update() {

}

void GUIMiniMap::render(Renderer *renderer, Event *event) {
    if(event->getPressed(SDL_SCANCODE_EQUALS) || event->getPressed(SDL_SCANCODE_KP_PLUS)) {
        range /= 2;
    }
    else if(event->getPressed(SDL_SCANCODE_MINUS) || event->getPressed(SDL_SCANCODE_KP_MINUS)) {
        range *= 2;
    }


    Vector point2 = renderer->getResolution() - Vector(margin, margin);
    Vector point1 = point2 - size;
    if(point1.quarter() == Vector::QUARTER_RIGHT_DOWN) {
        renderer->rect(point1, point2, DEFAULT_COLOR);

        for(Worker *worker : *units) {
            Unit *unit = dynamic_cast<Unit*>(worker);
            if(unit) {
                Vector posOnMap = ((unit->getPosition() - renderer->getCamera()->getPosition()) / range * size.module()) + (size / 2);

                if(posOnMap.quarter() == Vector::QUARTER_RIGHT_DOWN && (size - posOnMap).quarter() == Vector::QUARTER_RIGHT_DOWN) {
                    if(unit->is<Projectile*>()) {
                        renderer->square(point1 + posOnMap, 1, SELECTED_COLOR);
                    } else if (unit->isNot<LightParticle*>()) {
                        renderer->circle(point1 + posOnMap, 2, unit->is<Camera*>() ? SELECTED_COLOR >> 8 : SELECTED_COLOR << 8);
                    }
                }
            }
        }
    }
}
