#include "debug.h"
#include "gameapplication.h"

#include <src/engine/context.h>
#include <src/engine/assettools/assetprovider.h>
#include <src/engine/audio/abstractaudioprovider.h>
#include <src/engine/abstracteventhandler.h>
#include <src/engine/graphics/abstractrenderer.h>
#include <src/engine/graphics/abstractgraphicsprovider.h>


namespace e172 {


size_t GameApplication::static_constructor() {
    e172::Debug::installSigsegvHandler([](auto s){
        const auto st = e172::Debug::stackTrace();
        Debug::warning("Segmentation Fault");
        Debug::warning("Stack trace info:");
        for(auto s : st) {
            Debug::print('\t', s);
        }
        exit(s);
    });
    return 0;
}

std::vector<std::string> GameApplication::coverArgs(int argc, char *argv[]) {
    std::vector<std::string> result;
    for(int i = 0; i < argc; i++) {
        result.push_back(argv[i]);
    }
    return result;
}

ElapsedTimer::time_t GameApplication::renderDelay() const {
    return m_renderDelay;
}

ElapsedTimer::time_t GameApplication::proceedDelay() const {
    return m_proceedDelay;
}


void GameApplication::destroyAllEntities(Context *, const Variant &) {
    auto it = m_entities.begin();
    while (it != m_entities.end()) {
        if((*it)->liveInHeap()) {
            destroy(*it);
            it = m_entities.erase(it);
        } else {
            ++it;
        }
    }
}

void GameApplication::destroyEntity(Context*, const Variant &value) {
    for(auto it = m_entities.begin(); it != m_entities.end(); ++it) {
        if((*it)->entityId() == value.toNumber<Entity::id_t>()) {
            destroy(*it);
            m_entities.erase(it);
            return;
        }
    }
}

void GameApplication::destroyEntitiesWithTag(Context *, const Variant &value) {
    const auto tag = value.toString();

    auto it = m_entities.begin();
    while (it != m_entities.end()) {
        if((*it)->liveInHeap() && (*it)->containsTag(tag)) {
            destroy(*it);
            it = m_entities.erase(it);
        } else {
            ++it;
        }
    }
}


std::list<ptr<Entity> > GameApplication::entities() const {
    return m_entities;
}

ptr<Entity> GameApplication::autoIteratingEntity() const {
    return m_entities.cyclicValue(nullptr);
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

Context *GameApplication::context() const {
    return m_context;
}

AssetProvider *GameApplication::assetProvider() const {
    return m_assetProvider;
}

std::vector<std::string> GameApplication::arguments() const {
    return m_arguments;
}

void GameApplication::setRenderInterval(ElapsedTimer::time_t interval) {
    m_renderTimer = ElapsedTimer(interval);
}

void GameApplication::removeApplicationExtension(size_t hash) {
    const auto it = m_applicationExtensions.find(hash);
    if(it != m_applicationExtensions.end())
        m_applicationExtensions.erase(it);
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
    for(auto m : m_applicationExtensions) {
        if(m.second->extensionType() == GameApplicationExtension::InitExtension)
            m.second->proceed(this);
    }
    while (1) {
        m_deltaTimeCalculator.update();

        if(m_eventHandler) {
            m_eventHandler->update();
            if(m_eventHandler->exitFlag())
                break;
        }

        e172::ElapsedTimer measureTimer;
        for(auto m : m_applicationExtensions) {
            if(m.second->extensionType() == GameApplicationExtension::PreProceedExtension)
                m.second->proceed(this);
        }
        for(auto e : m_entities) {
            e->proceed(m_context, m_eventHandler);
            for(auto euf : e->__euf) {
                euf.first(e.data(), m_context, m_eventHandler);
            }
        }
        m_proceedDelay = measureTimer.elapsed();
        if(m_graphicsProvider && m_renderTimer.check()) {
            measureTimer.reset();
            auto r = m_graphicsProvider->renderer();
            if(r) {
                r->m_locked = false;
                for(auto m : m_applicationExtensions) {
                    if(m.second->extensionType() == GameApplicationExtension::PreRenderExtension)
                        m.second->proceed(this);
                }
                for(auto e : m_entities) {
                    e->render(r);
                    for(auto euf : e->__euf) {
                        euf.second(e.data(), r);
                    }
                }
                r->m_locked = true;
                if(!r->update()) {
                    break;
                }
            }
            m_renderDelay = measureTimer.elapsed();
        }

        //AUTO ITERATOR RESET MUST BE BEFORE DESTRUCTION HANDLING
        //if(++m_autoIterator == m_entities.end()) {
        //    m_autoIterator = m_entities.begin();
        //}
        m_entities.nextCycle();

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
