#include "additional.h"
#include "context.h"


#include "objectregistry.h"
#include "debug.h"
#include "units/particle.h"
#include "additional/lightparticle.h"
#include <math.h>
#include "assettools/assetprovider.h"
#include "gameapplication.h"

namespace e172 {

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


double Context::deltaTime() const {
    return m_deltaTime;
}

GameApplication *Context::appliation() const
{
    return m_appliation;
}

void Context::handleRequest(Request request) {
    PROTECT_OBJECT(request.requester)
    if(request.command == DELETE_UNIT) {
        Debug::out("DELETE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        const auto pos = std::find(m_entities->begin(), m_entities->end(), request.requester);
        if(pos != m_entities->end()) {
            m_entities->erase(pos);
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
                        particle->place(requester->position(), e172::Vector::createRandom(v0) + requesterAsMovable->velocity() * 0.5);
                    } else {
                        particle->place(requester->position(), e172::Vector::createRandom(v0) + requesterAsMovable->velocity());
                    }
                } else {
                    particle->place(requester->position(), e172::Vector::createRandom(v0));
                }
                m_entities->push_back(particle);
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
                particle->place(requester->position(), e172::Vector::createRandom(v0) / 2 + e172::Vector::createByAngle(requester->velocity().module() / 2, requester->getAngle()));
                m_entities->push_back(particle);
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
                    shipToSpawn->place(parent->position(), e172::Vector::createByAngle(parent->getReleaseSpead(), parent->getAngle()), e172::Vector(), parent->getAngle());
                } else if(unitToSpawn) {
                    unitToSpawn->place(parent->position(), 0.785);
                }
                m_entities->push_back(unitToSpawn);
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
            GUICentralMessage *element = new GUICentralMessage(message);
            element->start(2);
            //gui->setMessage(element);
        }
    } else if (request.command == BACKGROUND_FLASHING) {
        Debug::out("BACKGROUND_FLASHING: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        if(request.argument.isNumber()) {
            int repeats = request.argument.toInt32();
            //background->flashing(repeats);
        }
    } else if (request.command == FLOATING_MESSAGE) {
        Debug::out("FLOATING_MESSAGE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
        if(request.argument.isNumber()) {
            Unit *unit = dynamic_cast<Unit*>(request.requester);
            //if(unit) {
            //    gui->addBlushingFloatingMessage(unit, request.argument.toInt32());
            //}
        }
    }
}

Context::Context(std::list<Entity *> *entities, AssetProvider *assetProvider) {
    m_entities = entities;
    m_assetProvider = assetProvider;
}

std::string Context::absolutePath(const std::string &path) const {
    if(m_appliation) {
        const auto args = m_appliation->arguments();
        if(args.size() > 0) {
            return e172::Additional::absolutePath(path, args[0]);
        }
    }
    return std::string();
}

std::vector<std::string> Context::arguments() const {
    if(m_appliation)
        return m_appliation->arguments();
    return std::vector<std::string>();
}

std::list<Entity *> *Context::entities() const {
    return m_entities;
}


void Context::addEvent(Entity *requester, unsigned command, old::Variant argument) {
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

AssetProvider *Context::assetProvider() const {
    return m_assetProvider;
}
}
