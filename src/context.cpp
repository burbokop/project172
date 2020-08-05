#include "context.h"


#include "objectregistry.h"
#include "debug.h"
#include "units/particle.h"
#include "additional/lightparticle.h"
#include <math.h>

const unsigned Context::DELETE_UNIT = 0;
const unsigned Context::SPAWN_EXPLOSIVE = 1;
const unsigned Context::SPAWN_ENGINE_EXPLOSIVE = 2;
const unsigned Context::SPAWN_ENGINE_PARTICLES = 3;
const unsigned Context::SPAWN_UNIT = 4;
const unsigned Context::SPAWN_SURFACE = 5;
const unsigned Context::ADD_CAPABILITY = 6;
const unsigned Context::REMOVE_CAPABILITY = 7;

const unsigned Context::EMERGENCY_MESSAGE = 8;
const unsigned Context::BACKGROUND_FLASHING = 9;
const unsigned Context::FLOATING_MESSAGE = 10;

void Context::setGui(GUIMain *value) {
    gui = value;
}

void Context::setBackground(Background *value) {
    background = value;
}

void Context::setNear(Near *value) {
    _near = value;
}


void Context::handleRequest(Request request) {
    PROTECT_OBJECT(request.requester);
    if(request.command == DELETE_UNIT) {
        Debug::out("DELETE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        std::vector<Worker*>::iterator pos = std::find(units->begin(), units->end(), request.requester);
        if(pos != units->end()) {
            units->erase(pos);
            //std::cout << "deleted +++ " << request.requester.uncover() << " : " << request.requester.getDeleted() << " : " << *request.requester.getDeleted() << "\n";

            delete request.requester;
        }
    } else if (request.command == SPAWN_EXPLOSIVE || request.command == SPAWN_ENGINE_EXPLOSIVE) {
        Debug::out("BADABOOM: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        Unit *requester = dynamic_cast<Unit*>(request.requester);
        int radius = request.argument.isNumber() ? request.argument.toInt32() : 10;
        int v0 = static_cast<int>(std::sqrt(radius)) * 350;

        if(requester) {
            for(int i = 0; i < radius * 4; i++) {
                unsigned types[] = { Particle::PIXEL, Particle::CIRCLE, Particle::SQUARE };
                LightParticle *particle = new LightParticle(types[rand() % 3], radius * 600, radius * 400);
                Movable *requesterAsMovable = dynamic_cast<Movable*>(request.requester);
                if(requesterAsMovable) {
                    if(request.command == SPAWN_ENGINE_EXPLOSIVE) {
                        particle->place(requester->getPosition(), e172::Vector::createRandom(v0) + requesterAsMovable->getVelocity() * 0.5);
                    } else {
                        particle->place(requester->getPosition(), e172::Vector::createRandom(v0) + requesterAsMovable->getVelocity());
                    }
                } else {
                    particle->place(requester->getPosition(), e172::Vector::createRandom(v0));
                }
                units->push_back(particle);
            }
        }
    } else if (request.command == SPAWN_ENGINE_PARTICLES) {
        Debug::out("SPAWN_ENGINE_PARTICLES: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        Movable *requester = dynamic_cast<Movable*>(request.requester);
        int radius = request.argument.isNumber() ? request.argument.toInt32() : 10;
        int v0 = static_cast<int>(std::sqrt(radius));

        if(requester) {
            for(int i = 0; i < radius * 4; i++) {
                unsigned types[] = { Particle::PIXEL, Particle::CIRCLE, Particle::SQUARE };
                LightParticle *particle = new LightParticle(types[rand() % 3], radius * 600, radius * 400);
                particle->place(requester->getPosition(), e172::Vector::createRandom(v0) / 2 + e172::Vector::createByAngle(requester->getVelocity().module() / 2, requester->getAngle()));
                units->push_back(particle);
            }
        }
    } else if (request.command == SPAWN_UNIT) {
        Debug::out("SPAWN_UNIT: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));

        if(request.argument.isUnit()) {
            Unit *unitToSpawn = request.argument.toUnit();
            Ship *shipToSpawn = dynamic_cast<Ship*>(unitToSpawn);
            Ship *parent = dynamic_cast<Ship*>(request.requester);

            if(parent) {
                if(shipToSpawn) {
                    shipToSpawn->place(parent->getPosition(), e172::Vector::createByAngle(parent->getReleaseSpead(), parent->getAngle()), e172::Vector(), parent->getAngle());
                } else if(unitToSpawn) {
                    unitToSpawn->place(parent->getPosition(), 0.785);
                }
                units->push_back(unitToSpawn);
            }
        }
    } else if (request.command == SPAWN_SURFACE) {
        /**
         * SPAWN_SURFACE event is deprecated
         */


        /*
        Debug::out("SPAWN_SURFACE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));

        if(request.argument.isObject()) {
            SDL_Surface *surface = reinterpret_cast<SDL_Surface*>(request.argument.toObject());

            Animator anim = Animator(surface);
            anim.play(Animator::LOOP);
            Json::Value root;

            root["key"] = "sh1";
            root["class"] = "ship";
            root["health"] = 80;
            root["explosive"] = 64;

            Loadable *tmp = new Loadable(root, anim);
            Unit *unit = new Ship(tmp);

            if(unit) {
                unit->place(e172::Vector(), 0.0);
                units->push_back(unit);
            }
        }
        */
    } else if (request.command == ADD_CAPABILITY) {
        Debug::out("ADD_CAPABILITY: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        if(request.argument.isObject()) {
            Unit *unit = dynamic_cast<Unit*>(request.requester);
            Capability *capability = reinterpret_cast<Capability*>(request.argument.toObject());
            if(unit && capability) {
                unit->addCapability(capability);
            }
        }
    } else if (request.command == REMOVE_CAPABILITY) {
        Debug::out("REMOVE_CAPABILITY: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        if(request.argument.isObject()) {
            Unit *unit = dynamic_cast<Unit*>(request.requester);
            Capability *capability = reinterpret_cast<Capability*>(request.argument.toObject());
            if(unit && capability) {
                unit->removeCapability(capability);
            }
        }
    } else if (request.command == EMERGENCY_MESSAGE) {
        Debug::out("EMERGENCY_MESSAGE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        if(request.argument.isObject()) {
            const char *message = static_cast<char*>(request.argument.toObject());
            GUICentralMessage *element = new GUICentralMessage(nullptr, message);
            element->start(2);
            gui->setMessage(element);
        }
    } else if (request.command == BACKGROUND_FLASHING) {
        Debug::out("BACKGROUND_FLASHING: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        if(request.argument.isNumber()) {
            int repeats = request.argument.toInt32();
            background->flashing(repeats);
        }
    } else if (request.command == FLOATING_MESSAGE) {
        Debug::out("FLOATING_MESSAGE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        if(request.argument.isNumber()) {
            Unit *unit = dynamic_cast<Unit*>(request.requester);
            if(unit) {
                gui->addBlushingFloatingMessage(unit, request.argument.toInt32());
            }
        }
    }
}

Context::Context(std::vector<Worker *> *units, AssetManager *assets, GUIMain *gui) {
    this->units = units;
    this->assets = assets;
    this->gui = gui;
}

std::vector<Worker *> *Context::getUnits() const {
    return units;
}

AssetManager *Context::getAssets() const {
    return assets;
}


void Context::addEvent(Worker *requester, unsigned command, Variant argument) {
    eventQueue.push({
        requester,
        command,
        argument
    });
}


void Context::handleEvents() {
    while (eventQueue.size() > 0) {
        handleRequest(eventQueue.front());
        eventQueue.pop();
    }
}
