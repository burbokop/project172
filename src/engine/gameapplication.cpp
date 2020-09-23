#include "gameapplication.h"

#include <src/engine/context.h>
#include <src/engine/assettools/assetprovider.h>
#include <src/engine/audio/abstractaudioprovider.h>
#include <src/engine/abstracteventhandler.h>
#include <src/engine/graphics/abstractrenderer.h>
#include <src/engine/graphics/abstractgraphicsprovider.h>


namespace e172 {


std::vector<std::string> GameApplication::coverArgs(int argc, char *argv[]) {
    std::vector<std::string> result;
    for(int i = 0; i < argc; i++) {
        result.push_back(argv[i]);
    }
    return result;
}


void GameApplication::destroyAllEntities(Context *, const Variant &) {
    auto it = m_entities.begin();
    while (it != m_entities.end()) {
        if((*it)->liveInHeap()) {
            delete *it;
            it = m_entities.erase(it);

            if(m_autoIterator == m_entities.end()) {
                m_autoIterator = m_entities.begin();
            }
        } else {
            ++it;
        }
    }
}

void GameApplication::destroyEntity(Context* context, const Variant &value) {
    if(const auto e = context->entityById(value.toNumber<Entity::id_t>())) {
        if(e->liveInHeap()) {
            m_entities.remove(e);
            if(m_autoIterator != m_entities.begin())
                --m_autoIterator;

            if(m_autoIterator == m_entities.end()) {
                m_autoIterator = m_entities.begin();
            }

            delete e;
        }
    }
}

void GameApplication::destroyEntitiesWithTag(Context *, const Variant &value) {
    const auto tag = value.toString();

    auto it = m_entities.begin();
    while (it != m_entities.end()) {
        if((*it)->liveInHeap() && (*it)->containsTag(tag)) {
            delete *it;
            it = m_entities.erase(it);

            if(m_autoIterator == m_entities.end()) {
                m_autoIterator = m_entities.begin();
            }
        } else {
            ++it;
        }
    }
}


std::list<Entity *> GameApplication::entities() const
{
    return m_entities;
}

Entity *GameApplication::autoIteratingEntity() const {
    if(m_autoIterator != m_entities.end()) {
        return m_autoIterator.operator*();
    }
    return nullptr;
}

AbstractGraphicsProvider *GameApplication::graphicsProvider() const {
    return m_graphicsProvider;
}

void GameApplication::setGraphicsProvider(AbstractGraphicsProvider *graphicsProvider) {
    m_graphicsProvider = graphicsProvider;
    m_assetProvider->m_graphicsProvider = graphicsProvider;
}

AbstractAudioProvider *GameApplication::audioProvider() const {
    return m_audioProvider;
}

void GameApplication::setAudioProvider(AbstractAudioProvider *audioProvider) {
    m_audioProvider = audioProvider;
    m_assetProvider->m_audioProvider = audioProvider;
}

void GameApplication::setEventHandler(AbstractEventHandler *eventHandler) {
    m_eventHandler = eventHandler;
}

AbstractEventHandler *GameApplication::eventHandler() const {
    return m_eventHandler;
}

AbstractRenderer *GameApplication::renderer() const {
    if(m_graphicsProvider)
        return m_graphicsProvider->renderer();
    return nullptr;
}

Context *GameApplication::context() const {
    return m_context;
}

AssetProvider *GameApplication::assetProvider() const {
    return m_assetProvider;
}

std::vector<std::string> GameApplication::arguments() const {
    return m_arguments;
}

GameApplication::GameApplication(int argc, char *argv[]) {
    m_arguments = coverArgs(argc, argv);
    m_assetProvider = new AssetProvider();
    m_context = new Context(this);
    m_assetProvider->m_context = m_context;
}

void GameApplication::quit() {
    mustQuit = true;
}

int GameApplication::exec() {
    while (1) {
        m_deltaTimeCalculator.update();

        if(m_eventHandler) {
            m_eventHandler->update();
            if(m_eventHandler->exitFlag())
                break;
        }

        for(auto e : m_entities) {
            e->proceed(m_context, m_eventHandler);
            for(auto euf : e->__euf) {
                euf.first(e, m_context, m_eventHandler);
            }
        }

        if(m_graphicsProvider && m_renderTimer.check()) {
            auto r = m_graphicsProvider->renderer();
            if(r) {
                r->m_locked = false;
                for(auto m : m_applicationExtensions) {
                    if(m->extensionType() == GameApplicationExtension::PreRenderExtension)
                        m->proceed(this);
                }
                for(auto e : m_entities) {
                    e->render(r);
                    for(auto euf : e->__euf) {
                        euf.second(e, r);
                    }
                }
                r->m_locked = true;
                if(!r->update()) {
                    break;
                }
            }
        }

        //AUTO ITERATOR RESET MUST BE BEFORE DESTRUCTION HANDLING
        if(++m_autoIterator == m_entities.end()) {
            m_autoIterator = m_entities.begin();
        }

        if(m_context) {
            m_context->popMessage(Context::DESTROY_ENTITY, this, &GameApplication::destroyEntity);
            m_context->popMessage(Context::DESTROY_ALL_ENTITIES, this, &GameApplication::destroyAllEntities);
            m_context->popMessage(Context::DESTROY_ENTITIES_WITH_TAG, this, &GameApplication::destroyEntitiesWithTag);

            m_context->m_messageQueue.invokeInternalFunctions();
            m_context->m_messageQueue.flushMessages();
            m_context->m_deltaTime = m_deltaTimeCalculator.deltaTime();
        }

        if(mustQuit)
            break;
    }
    delete m_assetProvider;
    delete m_context;
    return 0;
}

GameApplicationExtension::ExtensionType GameApplicationExtension::extensionType() const {
    return m_extensionType;
}

void GameApplicationExtension::setExtensionType(const ExtensionType &extensionType) {
    m_extensionType = extensionType;
}

GameApplicationExtension::GameApplicationExtension(GameApplicationExtension::ExtensionType extensionType) {
    m_extensionType = extensionType;
}


}
