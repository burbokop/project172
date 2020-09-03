#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include "entity.h"

#include <vector>
#include <string>


#include <src/engine/time/deltatimecalculator.h>
#include <src/engine/time/elapsedtimer.h>
#include <list>


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
    std::vector<std::string> coverArgs(int argc, char *argv[]);
    std::vector<std::string> m_arguments;

    DeltaTimeCalculator m_deltaTimeCalculator;
    ElapsedTimer m_renderTimer;

    std::list<Entity*> m_entities;
    std::list<GameApplicationExtension*> m_applicationExtensions;

    AbstractEventHandler *m_eventHandler = nullptr;
    AbstractGraphicsProvider *m_graphicsProvider = nullptr;
    AbstractAudioProvider *m_audioProvider = nullptr;

    AssetProvider *m_assetProvider = nullptr;
    Context *m_context = nullptr;

    void destroyAllEntities(Context*, const Variant&);
    void destroyEntity(Context*context, const Variant&value);
public:
    GameApplication(int argc, char *argv[]);

    int exec();
    std::vector<std::string> arguments() const;

    inline void addEntity(Entity *entity) { m_entities.push_back(entity); }
    inline void addApplicationExtension(GameApplicationExtension *extension) { m_applicationExtensions.push_back(extension); }
    inline void removeApplicationExtension(GameApplicationExtension *extension) { m_applicationExtensions.remove(extension); }

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
};

}
#endif // GAMEAPPLICATION_H