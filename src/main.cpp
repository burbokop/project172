#include "additional/chartview.h"
#include "additional/memstatearner.h"
#include "additional/taskconsole.h"
#include "appextensions/screensettingsextension.h"
#include "appextensions/volumeobserverextension.h"
#include "assetexecutors/assetexecutors.h"
#include "background.h"
#include "capabilities/capabilities.h"
#include "capabilities/capabilitysynchronizer.h"
#include "debugchart.h"
#include "explosivespawner.h"
#include "flags.h"
#include "near.h"
#include "renderlayer.h"
#include "tasks/tasks.h"
#include "units/units.h"
#include "worldpresetstrategy.h"
#include "worlds/arenaworld.h"
#include "worlds/defaultworld.h"
#include "worlds/guimaker.h"
#include "worlds/heapworld.h"
#include <e172/assettools/assetprovider.h>
#include <e172/context.h>
#include <e172/debug.h>
#include <e172/gameapplication.h>
#include <e172/graphics/abstractgraphicsprovider.h>
#include <e172/impl/sdl/audioprovider.h>
#include <e172/impl/sdl/eventprovider.h>
#include <e172/net/linux/networker.h>
#include <e172/net/mem/networker.h>
#include <iostream>
#include <thread>

namespace proj172 {

void setupClient(e172::GameApplication &app,
                 const std::shared_ptr<e172::AbstractGraphicsProvider> &graphicsProvider,
                 const std::shared_ptr<e172::Networker> &net,
                 bool displayChart)
{
    using namespace proj172::core;
    app.setRenderInterval(1000 / 30);

    if (graphicsProvider) {
        graphicsProvider->renderer()->setAutoClear(false);
        graphicsProvider->loadFont(std::string(),
                                   app.context()->absolutePath("./assets/fonts/ZCOOL.ttf"));
        graphicsProvider->loadFont("Consolas",
                                   app.context()->absolutePath("./assets/fonts/consolas.ttf"));
    }

    if (net) {
        net->registerEntityType<WorldPresetStrategy>();
    }

    const auto background = e172::FactoryMeta::make<Background>(128);
    const auto camera = e172::FactoryMeta::make<Camera>();
    background->bindToPhysicalObject(camera);
    app.addEntity(background);
    app.addEntity(camera);

    app.addEntity(e172::FactoryMeta::make<MemStatEarner>());
    const auto radarNear = e172::FactoryMeta::make<Near>();
    app.addEntity(radarNear);

    //create task console
    const auto taskConsole = std::make_shared<TaskConsole>();
    registerConsoleTasks(*taskConsole);

    //setup gui
    GUIMaker guiMaker(app.context(), radarNear, taskConsole);
    app.addEntity(guiMaker.rootElement());

    const auto explosiveSpawner = e172::FactoryMeta::makeUniq<ExplosiveSpawner>();
    app.addEntity(explosiveSpawner.get());

    app.addApplicationExtension<ScreenSettingsExtension>();
    app.addApplicationExtension<VolumeObserverExtension>();

    if (displayChart) {
        addDebugChartToApp(app);
    }
}

void setupServer(e172::GameApplication &app)
{
    using namespace proj172::core;
    app.setProccedInterval(1000 / 30);

    const auto worldPresetStrategy = e172::FactoryMeta::make<WorldPresetStrategy>();
    worldPresetStrategy->registerType<DefaultWorld>();
    worldPresetStrategy->registerType<ArenaWorld>();
    worldPresetStrategy->registerType<HeapWorld>();
    app.addEntity(worldPresetStrategy);

    // TODO
    //worldPresetStrategy->controllersChanged(
    //    [&guiMaker, &camera, &radarNear](const std::list<e172::ptr<Controller>> &c) {
    //        if (c.size() > 0) {
    //            const auto controller = c.front();
    //            camera->setTarget(controller);
    //            guiMaker.rootElement()->setController(controller);
    //            radarNear->setCenter(controller);
    //        }
    //    });

    const auto presetNames = worldPresetStrategy->presetNames();
    if (presetNames.size() > 0) {
        worldPresetStrategy->activatePreset(worldPresetStrategy->presetNames().front());
    }

    // TODO
    //guiMaker.setWorldPresetStrategy(worldPresetStrategy.get());
}

void setupBoth(e172::GameApplication &app)
{
    using namespace proj172::core;
    registerAssetExecutors(*app.assetProvider());
    registerUnits(app);
    registerCapabilities(app);
    app.assetProvider()->addDirToSearch(app.context()->absolutePath("./assets"));
}

int server(int argc, const char **argv, const std::shared_ptr<e172::Networker> &net)
{
    e172::GameApplication app(argc, argv);
    app.setMode(e172::GameApplication::Mode::Proceed);

    auto server = net->listen(app, 4444).unwrap();
    std::cout << "listening in port " << 4444 << std::endl;
    app.setEventProvider(server);

    const auto capServer = std::make_shared<core::CapabilitySyncServer>(server);
    app.scheduleRepeated(1000 / 30, [server] {
        server->sync();
        static std::size_t i = 0;
        //std::cout << i++ << " statistics: " << server->statistics() << std::endl;
    });

    setupBoth(app);
    setupServer(app);
    return app.exec();
}

int client(int argc,
           const char **argv,
           const std::shared_ptr<e172::Networker> &net,
           bool displayChart)
{
    e172::GameApplication app(argc, argv);
    app.setMode(e172::GameApplication::Mode::Render);
    const auto graphicsProvider = chooseGraphicsProvider(app);
    std::cout << "Graphics provider choosed" << std::endl;
    app.setEventProvider(std::make_shared<e172::impl::sdl::EventProvider>());
    app.setAudioProvider(std::make_shared<e172::impl::sdl::AudioProvider>());
    app.setGraphicsProvider(graphicsProvider);

    auto client = net->connect(app, 4444).unwrap();
    const auto capClient = std::make_shared<core::CapabilitySyncClient>(client);

    app.scheduleRepeated(1000 / 30, [client] {
        client->sync();
        //std::cout << "statistics: " << client->statistics() << std::endl;
    });

    setupBoth(app);
    setupClient(app, graphicsProvider, net, displayChart);
    return app.exec();
}

int both(int argc, const char **argv, bool displayChart)
{
    e172::GameApplication app(argc, argv);
    const auto graphicsProvider = chooseGraphicsProvider(app);
    app.setEventProvider(std::make_shared<e172::impl::sdl::EventProvider>());
    app.setAudioProvider(std::make_shared<e172::impl::sdl::AudioProvider>());
    app.setGraphicsProvider(graphicsProvider);

    setupBoth(app);
    setupServer(app);
    setupClient(app, graphicsProvider, nullptr, displayChart);
    return app.exec();
}

int mock(int argc, const char **argv, bool displayChart)
{
    std::shared_ptr<e172::Networker> net = std::make_shared<e172::MemNetworker>();
    std::thread serverThread([argc, argv, net] { server(argc, argv, net); });
    return client(argc, argv, net, displayChart);
}

} // namespace proj172

int old(int argc, const char **argv);

int main(int argc, const char **argv)
{
    using namespace proj172;
    e172::Debug::print("compiler:", e172::Debug::compilerInfo());
    const auto flags = Flags::parseOrDie(argc, argv);
    std::cout << "flags: " << flags << std::endl;
    switch (flags.mode) {
    case proj172::AppMode::Server:
        return server(argc, argv, std::make_shared<e172::LinuxNetworker>());
    case proj172::AppMode::Client:
        return client(argc, argv, std::make_shared<e172::LinuxNetworker>(), flags.displayChart);
    case proj172::AppMode::Both:
        return both(argc, argv, flags.displayChart);
    case proj172::AppMode::Mock:
        return mock(argc, argv, flags.displayChart);
    case proj172::AppMode::Old:
        return old(argc, argv);
    }
}

int old(int argc, const char **argv)
{
    using namespace proj172;
    using namespace proj172::core;

    const auto flags = Flags::parseOrDie(argc, argv);

    e172::GameApplication app(argc, argv);

    const auto graphicsProvider = chooseGraphicsProvider(app);

    app.setRenderInterval(1000 / 30);

    app.setEventProvider(std::make_shared<e172::impl::sdl::EventProvider>());
    app.setAudioProvider(std::make_shared<e172::impl::sdl::AudioProvider>());
    app.setGraphicsProvider(graphicsProvider);

    registerAssetExecutors(*app.assetProvider());
    registerUnits(app);
    registerCapabilities(app);

    app.assetProvider()->addDirToSearch(app.context()->absolutePath("./assets"));

    graphicsProvider->renderer()->setAutoClear(false);
    graphicsProvider->loadFont(std::string(),
                               app.context()->absolutePath("./assets/fonts/ZCOOL.ttf"));
    graphicsProvider->loadFont("Consolas",
                               app.context()->absolutePath("./assets/fonts/consolas.ttf"));

    //APP INITIALIZATION CONMPLEATED

    //initialization background
    const auto background = e172::FactoryMeta::makeUniq<Background>(128);
    app.addEntity(background.get());

    //mem stat
    const auto memStat = e172::FactoryMeta::makeUniq<MemStatEarner>();
    app.addEntity(memStat.get());

    //setup radar near
    const auto radarNear = e172::FactoryMeta::makeUniq<Near>();
    app.addEntity(radarNear.get());

    //create task console
    const auto &taskConsole = std::make_shared<TaskConsole>();
    registerConsoleTasks(*taskConsole);

    //setup gui
    GUIMaker guiMaker(app.context(), radarNear.get(), taskConsole);
    app.addEntity(guiMaker.rootElement());

    //setup camera
    const auto camera = e172::FactoryMeta::makeUniq<Camera>();
    app.addEntity(camera.get());
    background->bindToPhysicalObject(camera.get());

    //setup world strategy
    const auto worldPresetStrategy = e172::FactoryMeta::makeUniq<WorldPresetStrategy>();
    worldPresetStrategy->registerType<DefaultWorld>();
    worldPresetStrategy->registerType<ArenaWorld>();
    worldPresetStrategy->registerType<HeapWorld>();
    app.addEntity(worldPresetStrategy.get());

    worldPresetStrategy->controllersChanged(
        [&guiMaker, &camera, &radarNear](const std::list<e172::ptr<Controller>> &c) {
            if (c.size() > 0) {
                const auto controller = c.front();
                camera->setTarget(controller);
                guiMaker.rootElement()->setController(controller);
                radarNear->setCenter(controller);
            }
        });

    const auto presetNames = worldPresetStrategy->presetNames();
    if (presetNames.size() > 0) {
        worldPresetStrategy->activatePreset(worldPresetStrategy->presetNames().front());
    }

    guiMaker.setWorldPresetStrategy(worldPresetStrategy.get());

    //independent services initialization

    const auto explosiveSpawner = e172::FactoryMeta::makeUniq<ExplosiveSpawner>();
    app.addEntity(explosiveSpawner.get());

    app.addApplicationExtension<ScreenSettingsExtension>();
    app.addApplicationExtension<VolumeObserverExtension>();

    if (flags.displayChart) {
        addDebugChartToApp(app);
    }

    return app.exec();
}
