#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include "entity.h"

#include <vector>
#include <string>


#include <src/engine/time/deltatimecalculator.h>
#include <src/engine/time/elapsedtimer.h>
#include <list>
#include <src/engine/type.h>

namespace e172 {
class AbstractAudioProvider;
class AbstractGraphicsProvider;
class AssetProvider;
class Context;

class GameApplication;

class GameApplicationExtension {
public:
    enum ExtensionType {
        UndefinedExtension,
        InitExtension,
        PreProceedExtension,
        PreRenderExtension
    };
    ExtensionType extensionType() const;
protected:
    void setExtensionType(const ExtensionType &extensionType);
private:
    ExtensionType m_extensionType = UndefinedExtension;
public:
    GameApplicationExtension(ExtensionType extensionType);
    virtual void proceed(GameApplication *application) = 0;
};


class GameApplication {
    static size_t static_constructor();
    static const inline size_t static_call = static_constructor();

    std::vector<std::string> coverArgs(int argc, char *argv[]);
    std::vector<std::string> m_arguments;

    DeltaTimeCalculator m_deltaTimeCalculator;
    ElapsedTimer m_renderTimer;

    std::list<Entity*> m_entities;
    std::map<size_t, GameApplicationExtension*> m_applicationExtensions;

    AbstractEventHandler *m_eventHandler = nullptr;
    AbstractGraphicsProvider *m_graphicsProvider = nullptr;
    AbstractAudioProvider *m_audioProvider = nullptr;

    AssetProvider *m_assetProvider = nullptr;
    Context *m_context = nullptr;

    void destroyAllEntities(Context*, const Variant&);
    void destroyEntity(Context*context, const Variant& value);
    void destroyEntitiesWithTag(Context*, const Variant& value);

    bool mustQuit = false;

    std::list<Entity*>::iterator m_autoIterator = m_entities.begin();
public:
    GameApplication(int argc, char *argv[]);

    void quit();

    int exec();
    std::vector<std::string> arguments() const;

    inline void addEntity(Entity *entity) { m_entities.push_back(entity); }
    template<typename T>
    inline void addApplicationExtension() {
        const auto it = m_applicationExtensions.find(Type<T>::hash());
        if(it == m_applicationExtensions.end())
            m_applicationExtensions[Type<T>::hash()] = new T();
    }
    template<typename T>
    inline void removeApplicationExtension() {
        removeApplicationExtension(Type<T>::hash());
    }
    inline void removeApplicationExtension(size_t hash) {
        const auto it = m_applicationExtensions.find(hash);
        if(it != m_applicationExtensions.end())
            m_applicationExtensions.erase(it);
    }

    AssetProvider *assetProvider() const;
    e172::Context *context() const;
    AbstractEventHandler *eventHandler() const;

    [[deprecated]]
    AbstractRenderer *renderer() const;
    AbstractAudioProvider *audioProvider() const;
    AbstractGraphicsProvider *graphicsProvider() const;

    void setEventHandler(AbstractEventHandler *eventHandler);
    void setAudioProvider(AbstractAudioProvider *audioProvider);
    void setGraphicsProvider(AbstractGraphicsProvider *graphicsProvider);
    std::list<Entity *> entities() const;

    Entity *autoIteratingEntity() const;

};

}
#endif // GAMEAPPLICATION_H
