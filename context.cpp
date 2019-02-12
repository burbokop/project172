#include "context.h"

const Uint8 Context::DELETE_UNIT = 0;
const Uint8 Context::SPAWN_EXPLOSIVE = 1;
const Uint8 Context::SPAWN_UNIT = 2;
const Uint8 Context::SPAWN_SURFACE = 3;
const Uint8 Context::ADD_CAPABILITY = 4;
const Uint8 Context::REMOVE_CAPABILITY = 5;

const Uint8 Context::EMERGENCY_MESSAGE = 6;
const Uint8 Context::BACKGROUND_FLASHING = 7;
const Uint8 Context::FLOATING_MESSAGE = 8;


#include <iostream>

double rv() {
    double result = (static_cast<double>(rand() % 20) - 10) / 5.0;
    std::cout << "result: " << result << "\n";
    return result;
}

void Context::setGui(GUIMain *value) {
    gui = value;
}

void Context::setBackground(Background *value)
{
    background = value;
}

void Context::handleRequest(Request request) {
    if(request.command == DELETE_UNIT) {
        std::cout << "DELETE: " << request.requester << "\n";
        std::vector<Worker*>::iterator pos = std::find(units->begin(), units->end(), request.requester);
        if(pos != units->end()) {
            units->erase(pos);
        }
    } else if (request.command == SPAWN_EXPLOSIVE) {

        Unit *requester = dynamic_cast<Unit*>(request.requester);
        if(requester) {
            std::cout << "BADABOOM: " << request.requester << "\n";

            for(int i = 0; i < 26; i++) {
                Uint8 types[] = { Particle::PIXEL, Particle::CIRCLE, Particle::SQUARE };

                if(false) {
                    Particle *particle = new Particle(types[rand() % 3]);
                    particle->place(requester->getPosition(), Vector(rv(), rv()));
                    units->push_back(particle);
                } else {
                    LightParticle *particle = new LightParticle(types[rand() % 3]);
                    particle->place(requester->getPosition(), Vector(rv(), rv()));
                    units->push_back(particle);

                }

            }
        }
    } else if (request.command == SPAWN_UNIT) {
        if(request.argument.isObject()) {

            Unit *unitToSpawn = reinterpret_cast<Ship*>(request.argument.toObject());
            Ship *shipToSpawn = dynamic_cast<Ship*>(unitToSpawn);
            Ship *parent = dynamic_cast<Ship*>(request.requester);

            if(parent) {
                if(shipToSpawn) {
                    shipToSpawn->place(parent->getPosition(), Vector::createByAngle(parent->getReleaseSpead(), parent->getAngle()), Vector(), parent->getAngle());
                } else if(unitToSpawn) {
                    unitToSpawn->place(parent->getPosition(), 0.785);
                }
                units->push_back(unitToSpawn);
            }
        }
    } else if (request.command == SPAWN_SURFACE) {
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
                unit->place(Vector(), 0.0);
                units->push_back(unit);
            }
        }
    } else if (request.command == ADD_CAPABILITY) {
        if(request.argument.isObject()) {
            Unit *unit = dynamic_cast<Unit*>(request.requester);
            Capability *capability = reinterpret_cast<Capability*>(request.argument.toObject());
            if(unit && capability) {
                unit->addCapability(capability);
            }
        }
    } else if (request.command == REMOVE_CAPABILITY) {
        if(request.argument.isObject()) {
            Unit *unit = dynamic_cast<Unit*>(request.requester);
            Capability *capability = reinterpret_cast<Capability*>(request.argument.toObject());
            if(unit && capability) {
                unit->removeCapability(capability);
            }
        }
    } else if (request.command == EMERGENCY_MESSAGE) {
        if(request.argument.isObject()) {
            const char *message = static_cast<char*>(request.argument.toObject());
            std::cout << "message: " << message << "\n";

            GUICentralMessage *element = new GUICentralMessage(nullptr, message);
            element->start(2);
            gui->setMessage(element);
        }
    } else if (request.command == BACKGROUND_FLASHING) {
        if(request.argument.isNumber()) {
            int repeats = request.argument.toInt32();
            background->flashing(repeats);
        }
    } else if (request.command == FLOATING_MESSAGE) {
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


void Context::addEvent(Worker *requester, Uint8 command, Auto argument) {
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
