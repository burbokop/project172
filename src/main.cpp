#include "appextensions/screensettingsextension.h"
#include "explosivespawner.h"
#include "src/capabilities/docker.h"

#include <src/additional.h>
#include <src/context.h>
#include <src/debug.h>
#include <src/gameapplication.h>
#include <src/sdleventprovider.h>

#include <src/sdlaudioprovider.h>
#include <src/sdlgraphicsprovider.h>
#include <iostream>

#include <src/assetexecutors/animatorassetexecutor.h>
#include <src/assetexecutors/audioassetexecutor.h>
#include <src/assetexecutors/factoryassetexecutor.h>
#include <src/assetexecutors/nodesassetexecutor.h>
#include <src/assetexecutors/spriteassetexecutor.h>
#include <src/assetexecutors/templatevectorassetexecutor.h>
#include <src/assetexecutors/vectorassetexecutor.h>

#include <src/capabilities/ai.h>
#include <src/capabilities/factory.h>
#include <src/capabilities/player.h>

#include <src/worlds/arenaworld.h>
#include <src/worlds/defaultworld.h>
#include <src/worlds/guimaker.h>
#include <src/worlds/heapworld.h>

#include <src/background.h>

#include <vulkan_implementation/src/vulkangraphicsprovider.h>

#include <src/additional/chartview.h>
#include <src/additional/taskconsole.h>
#include <src/additional/memstatearner.h>
#include <src/gui/guibutton.h>
#include <src/gui/base/guicontainer.h>
#include <src/gui/base/guimenu.h>
#include <src/units/projectile.h>
#include <src/units/ship.h>
#include <src/units/station.h>
#include <src/capabilities/modules/engine.h>
#include <src/capabilities/modules/thruster.h>
#include <src/capabilities/modules/warpdrive.h>
#include <src/capabilities/modules/weapon.h>
#include <src/appextensions/volumeobserverextension.h>
#include <src/tasks/buywaretask.h>
#include <src/tasks/sellwaretask.h>
#include <src/tasks/tradetask.h>
#include <console_impl/src/consolegraphicsprovider.h>

//template<typename T, typename... Args>
//concept MetaType = requires(T v, e172::FactoryMeta &&meta, Args &&...args) {
//    {
//        T(meta, args...)
//    };
//};

int main(int argc, const char **argv)
{
    using namespace proj172::core;

    e172::Debug::print("compiler:", e172::Debug::compilerInfo());
    enum RendererUsing {
        Undefined,
        SDL,
        Vulkan,
        Console
    };
    RendererUsing rendererUsing = Undefined;
    {
        e172::GameApplication chooseGraphicsProviderApp(argc, argv);
        const auto gprovider
            = std::make_shared<SDLGraphicsProvider>(chooseGraphicsProviderApp.arguments(),
                                                    "choose gprovider",
                                                    e172::Vector<std::uint32_t>{118, 168});
        const auto eventProvider = std::make_shared<SDLEventProvider>();
        chooseGraphicsProviderApp.setGraphicsProvider(gprovider);
        chooseGraphicsProviderApp.setEventProvider(eventProvider);

        const auto background = e172::FactoryMeta::makeUniq<Background>(32);
        chooseGraphicsProviderApp.addEntity(background.get());

        const auto rootElement = e172::FactoryMeta::makeUniq<GUIContainer>();
        const auto stack = e172::FactoryMeta::makeUniq<GUIStack>();
        const auto menu = e172::FactoryMeta::makeUniq<GUIMenu>("renderer");
        const auto apply = [&rendererUsing, &chooseGraphicsProviderApp](e172::Variant value) {
            rendererUsing = static_cast<RendererUsing>(value.toInt());
            chooseGraphicsProviderApp.quitLater();
        };
        menu->addMenuElement(
            e172::FactoryMeta::make<GUIButton>(std::string("SDL2"), [apply](auto) { apply(SDL); }));
        menu->addMenuElement(e172::FactoryMeta::make<GUIButton>(std::string("Vulkan"),
                                                                [apply](auto) { apply(Vulkan); }));
        menu->addMenuElement(e172::FactoryMeta::make<GUIButton>(std::string("Console"),
                                                                [apply](auto) { apply(Console); }));

        stack->push(menu.get());
        rootElement->addChildElement(stack.get());

        gprovider->loadFont(std::string(),
                            chooseGraphicsProviderApp.context()->absolutePath(
                                "./assets/fonts/ZCOOL.ttf"));

        chooseGraphicsProviderApp.addEntity(rootElement.get());
        chooseGraphicsProviderApp.exec();
    }

    e172::GameApplication app(argc, argv);

    std::shared_ptr<e172::AbstractGraphicsProvider> graphicsProvider;
    if(rendererUsing == Vulkan) {
        graphicsProvider = std::make_shared<VulkanGraphicsProvider>(app.arguments());
        if(!graphicsProvider->isValid()) {
            graphicsProvider
                = std::make_shared<SDLGraphicsProvider>(app.arguments(),
                                                        "project172",
                                                        e172::Vector<std::uint32_t>{900, 600});
            if(!graphicsProvider->isValid()) {
                e172::Debug::fatal("error: no graphics provider are valid.");
                return -1;
            }
        }
    } else if(rendererUsing == SDL) {
        graphicsProvider = std::make_shared<SDLGraphicsProvider>(app.arguments(),
                                                                 "project172",
                                                                 e172::Vector<std::uint32_t>{900,
                                                                                             600});
    } else if(rendererUsing == Console) {
        graphicsProvider = std::make_shared<ConsoleGraphicsProvider>(app.arguments(), std::cout);
    } else {
        return 0;
    }

    app.setRenderInterval(1000 / 30);

    const auto eventProvider = std::make_shared<SDLEventProvider>();
    const auto audioProvider = std::make_shared<SDLAudioProvider>();
    app.setEventProvider(eventProvider);
    app.setAudioProvider(audioProvider);
    app.setGraphicsProvider(graphicsProvider);

    app.graphicsProvider()->renderer()->setAutoClear(false);

    app.assetProvider()->installExecutor("animation", std::make_shared<AnimatorAssetExecutor>());
    app.assetProvider()->installExecutor("sprite", std::make_shared<SpriteAssetExecutor>());
    app.assetProvider()->installExecutor("audio", std::make_shared<AudioAssetExecutor>());
    app.assetProvider()->installExecutor("offset", std::make_shared<VectorAssetExecutor>());
    app.assetProvider()->installExecutor("input", std::make_shared<RecieptAssetExecutor>());
    app.assetProvider()->installExecutor("output", std::make_shared<RecieptAssetExecutor>());
    app.assetProvider()->installExecutor("capabilities", std::make_shared<TemplateVectorAssetExecutor>());
    app.assetProvider()->installExecutor("nodes", std::make_shared<NodesAssetExecutor>());



    app.assetProvider()->registerType<Unit>();
    app.assetProvider()->registerType<Ship>();
    app.assetProvider()->registerType<Station>();
    app.assetProvider()->registerType<Projectile>();
    app.assetProvider()->registerType<Player>();
    app.assetProvider()->registerType<Engine>();
    app.assetProvider()->registerType<Weapon>();
    app.assetProvider()->registerType<WarpDrive>();
    app.assetProvider()->registerType<Thruster>();
    app.assetProvider()->registerType<Factory>();
    app.assetProvider()->registerType<Docker>();

    app.assetProvider()->searchInFolder(app.context()->absolutePath("./assets"));
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
    TaskConsole taskConsole;

    taskConsole.registerTask<DockingTask>();
    taskConsole.registerTask<BuyWareTask>();
    taskConsole.registerTask<SellWareTask>();
    taskConsole.registerTask<TradeTask>();

    //setup gui
    GUIMaker guiMaker(app.context(), radarNear.get(), &taskConsole);
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

    //debug utitlity
    const auto chartView = e172::FactoryMeta::makeUniq<ChartView>();

    //const auto f = [](double x, double x0){
    //    return std::sqrt(x) * x * 0.5;
    //};


    const auto f = [](double x, double x0) {
        if(x0 != e172::Math::null) {
            const auto a = (1 - x / x0);
            if(a != e172::Math::null) {
                return x * std::abs(1 / a - 1) * 2;
            }
        }
        return 0.;
    };

    //const auto f = [](double x, double x0){
    //    return std::pow(2, x) - 1;
    //};

    chartView->setOffset({100, 500});
    chartView->setFunction(f);
    chartView->setCoeficient(200);
    chartView->setPointCount(300);
    //app.addEntity(&chartView);

    //start application

    return app.exec();
}
