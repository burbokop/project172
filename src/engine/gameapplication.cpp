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
    for(auto e : m_entities) {
        delete e;
    }
    m_entities.clear();
}

void GameApplication::destroyEntity(Context* context, const Variant &value) {
    if(const auto e = context->entityById(value.toNumber<Entity::id_t>())) {
        m_entities.remove(e);
        delete e;
    }
}


std::list<Entity *> GameApplication::entities() const
{
    return m_entities;
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
                }
                r->m_locked = true;
                if(!r->update()) {
                    break;
                }
            }
        }

        if(m_context) {
            m_context->popMessage(Context::DELETE_UNIT, this, &GameApplication::destroyEntity);
            m_context->popMessage(Context::DELETE_ALL_UNITS, this, &GameApplication::destroyAllEntities);

            m_context->m_messageQueue.invokeInternalFunctions();
            m_context->m_messageQueue.flushMessages();
            m_context->m_deltaTime = m_deltaTimeCalculator.deltaTime();
        }
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
