#include "gameapplication.h"

#include <engine/context.h>
#include <engine/assettools/assetprovider.h>
#include <engine/audio/abstractaudioprovider.h>
#include <engine/abstracteventhandler.h>
#include <engine/graphics/abstractrenderer.h>
#include <engine/graphics/abstractgraphicsprovider.h>

namespace e172 {


std::vector<std::string> GameApplication::coverArgs(int argc, char *argv[]) {
    std::vector<std::string> result;
    for(int i = 0; i < argc; i++) {
        result.push_back(argv[i]);
    }
    return result;
}

AbstractGraphicsProvider *GameApplication::graphicsProvider() const {
    return m_graphicsProvider;
}

void GameApplication::setGraphicsProvider(AbstractGraphicsProvider *graphicsProvider) {
    m_graphicsProvider = graphicsProvider;
}

AbstractAudioProvider *GameApplication::audioProvider() const {
    return m_audioProvider;
}

void GameApplication::setAudioProvider(AbstractAudioProvider *audioProvider) {
    m_audioProvider = audioProvider;
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

GameApplication::GameApplication(int argc, char *argv[]) {
    m_arguments = coverArgs(argc, argv);
    m_assetProvider = new AssetProvider();
    m_context = new Context(&m_entities, m_assetProvider);
    m_context->m_appliation = this;
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
                for(auto e : m_entities) {
                    e->render(r);
                }
                r->update();
            }
        }

        if(m_context) {
            m_context->handleEvents();
            m_context->m_deltaTime = m_deltaTimeCalculator.deltaTime();
        }
    }
    delete m_assetProvider;
    delete m_context;
    return 0;
}


}
