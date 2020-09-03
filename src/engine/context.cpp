#include "additional.h"
#include "context.h"


#include "objectregistry.h"
#include "gameapplication.h"

namespace e172 {


double Context::deltaTime() const {
    return m_deltaTime;
}

AssetProvider *Context::assetProvider() const {
    if(m_application)
        return m_application->assetProvider();
    return nullptr;
}

std::list<Entity*> Context::entities() const {
    if(m_application)
        return m_application->entities();
    return std::list<Entity*>();
}

void Context::addEntity(Entity *entity) {
    m_application->addEntity(entity);
}


//void Context::handleRequest(Request request) {
//    PROTECT_OBJECT(request.requester)
//            if(request.command == DELETE_UNIT) {
//        Debug::out("DELETE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
//        const auto pos = std::find(m_entities->begin(), m_entities->end(), request.requester);
//        if(pos != m_entities->end()) {
//            m_entities->erase(pos);
//            delete request.requester;
//        }
//    } else if (request.command == SPAWN_ENGINE_PARTICLES) {
//        Debug::out("SPAWN_ENGINE_PARTICLES: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
//        Movable *requester = dynamic_cast<Movable*>(request.requester);
//        int radius = request.argument.isNumber() ? request.argument.toInt32() : 10;
//        int v0 = static_cast<int>(std::sqrt(radius));
//
//        if(requester) {
//            for(int i = 0; i < radius * 4; i++) {
//                unsigned types[] = { Particle::PIXEL, Particle::CIRCLE, Particle::SQUARE };
//                LightParticle *particle = new LightParticle(types[rand() % 3], radius * 600, radius * 400);
//                particle->place(requester->position(), e172::Vector::createRandom(v0) / 2 + e172::Vector::createByAngle(requester->velocity().module() / 2, requester->getAngle()));
//                m_entities->push_back(particle);
//            }
//        }
//    } else if (request.command == SPAWN_UNIT) {
//        Debug::out("SPAWN_UNIT: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
//
//        if(request.argument.isUnit()) {
//            Unit *unitToSpawn = request.argument.toUnit();
//            Ship *shipToSpawn = dynamic_cast<Ship*>(unitToSpawn);
//            Ship *parent = dynamic_cast<Ship*>(request.requester);
//
//            if(parent) {
//                if(shipToSpawn) {
//                    shipToSpawn->place(parent->position(), e172::Vector::createByAngle(parent->getReleaseSpead(), parent->getAngle()), e172::Vector(), parent->getAngle());
//                } else if(unitToSpawn) {
//                    unitToSpawn->place(parent->position(), 0.785);
//                }
//                m_entities->push_back(unitToSpawn);
//            }
//        }
//    } else if (request.command == SPAWN_SURFACE) {
//        /**
//         * SPAWN_SURFACE event is deprecated
//         */
//
//
//        /*
//        Debug::out("SPAWN_SURFACE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
//
//        if(request.argument.isObject()) {
//            SDL_Surface *surface = reinterpret_cast<SDL_Surface*>(request.argument.toObject());
//
//            Animator anim = Animator(surface);
//            anim.play(Animator::LOOP);
//            Json::Value root;
//
//            root["key"] = "sh1";
//            root["class"] = "ship";
//            root["health"] = 80;
//            root["explosive"] = 64;
//
//            Loadable *tmp = new Loadable(root, anim);
//            Unit *unit = new Ship(tmp);
//
//            if(unit) {
//                unit->place(e172::Vector(), 0.0);
//                units->push_back(unit);
//            }
//        }
//        */
//    } else if (request.command == ADD_CAPABILITY) {
//        Debug::out("ADD_CAPABILITY: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
//        if(request.argument.isObject()) {
//            Unit *unit = dynamic_cast<Unit*>(request.requester);
//            Capability *capability = reinterpret_cast<Capability*>(request.argument.toObject());
//            if(unit && capability) {
//                unit->addCapability(capability);
//            }
//        }
//    } else if (request.command == REMOVE_CAPABILITY) {
//        Debug::out("REMOVE_CAPABILITY: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
//        if(request.argument.isObject()) {
//            Unit *unit = dynamic_cast<Unit*>(request.requester);
//            Capability *capability = reinterpret_cast<Capability*>(request.argument.toObject());
//            if(unit && capability) {
//                unit->removeCapability(capability);
//            }
//        }
//    } else if (request.command == EMERGENCY_MESSAGE) {
//        Debug::out("EMERGENCY_MESSAGE: " + std::to_string(reinterpret_cast<uintptr_t>(request.requester)));
//        if(request.argument.isObject()) {
//            const char *message = static_cast<char*>(request.argument.toObject());
//            GUICentralMessage *element = new GUICentralMessage(message);
//            element->start(2);
//            //gui->setMessage(element);
//        }
//    }
//}

Context::Context(GameApplication *application) {
    m_application = application;
    m_messageQueue.setExceptionHandlingMode(decltype (m_messageQueue)::WarningException);
    m_messageQueue.setMessageLifeTime(1);
}

std::string Context::absolutePath(const std::string &path) const {
    if(m_application) {
        const auto args = m_application->arguments();
        if(args.size() > 0) {
            return e172::Additional::absolutePath(path, args[0]);
        }
    }
    return std::string();
}

std::vector<std::string> Context::arguments() const {
    if(m_application)
        return m_application->arguments();
    return std::vector<std::string>();
}

Promice *Context::emitMessage(const MessageId &messageId, const Variant &value) {
    return m_messageQueue.emitMessage(messageId, value);
}

bool Context::containsMessage(const MessageId &messageId) {
    return m_messageQueue.containsMessage(messageId);
}

Variant Context::popMessage(const MessageId &messageId, bool *ok) {
    return m_messageQueue.popMessage(messageId, ok);
}

Entity *Context::entityById(const Entity::id_t &id) const {
    const auto e = m_application->entities();
    for(auto a : e) {
        if(a && a->entityId() == id)
            return a;
    }
    return nullptr;
}


}