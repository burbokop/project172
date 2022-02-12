#include "explosivespawner.h"
#include "appextensions/screensettingsextension.h"

#include <src/gameapplication.h>
#include <src/context.h>
#include <src/debug.h>
#include <src/additional.h>

#include <src/sdlaudioprovider.h>
#include <src/sdleventhandler.h>
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

#include <bitset>

int f(int x) {
    int count = 0;
    std::cout << ":" << x << " - " << std::bitset<sizeof (int)>(x) << "\n";
    while (x) {
        count++;
        x = x&(x - 1);
        std::cout << ":" << x << " - " << std::bitset<sizeof (int)>(x) << "\n";
    }
    return count;
}

void aaa(const int& x) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void aaa(int&& x) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main(int argc, char *argv[]) {
    f(11);

    int a = 0;

    aaa(a);

    aaa(f(11));

    aaa(std::move(a));

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
        SDLGraphicsProvider gprovider(chooseGraphicsProviderApp.arguments(), "choose gprovider", 118, 168);
        SDLEventHandler eventHandler;
        chooseGraphicsProviderApp.setGraphicsProvider(&gprovider);
        chooseGraphicsProviderApp.setEventHandler(&eventHandler);

        Background background = 32;
        chooseGraphicsProviderApp.addEntity(&background);

        GUIContainer rootElement;
        GUIStack stack;
        GUIMenu menu("renderer");
        const auto apply = [&rendererUsing, &chooseGraphicsProviderApp](e172::Variant value) {
            rendererUsing = static_cast<RendererUsing>(value.toInt());
            chooseGraphicsProviderApp.quitLater();
        };
        menu.addMenuElement(new GUIButton(std::string("SDL2"), [apply](auto) { apply(SDL); }));
        menu.addMenuElement(new GUIButton(std::string("Vulkan"), [apply](auto) { apply(Vulkan); }));
        menu.addMenuElement(new GUIButton(std::string("Console"), [apply](auto) { apply(Console); }));

        stack.push(&menu);
        rootElement.addChildElement(&stack);

        gprovider.loadFont(std::string(), chooseGraphicsProviderApp.context()->absolutePath("../assets/fonts/ZCOOL.ttf"));

        chooseGraphicsProviderApp.addEntity(&rootElement);
        chooseGraphicsProviderApp.exec();
    }


    e172::GameApplication app(argc, argv);

    e172::AbstractGraphicsProvider *graphicsProvider = nullptr;
    if(rendererUsing == Vulkan) {
        graphicsProvider = new VulkanGraphicsProvider(app.arguments());
        if(!graphicsProvider->isValid()) {
            delete graphicsProvider;
            graphicsProvider = new SDLGraphicsProvider(app.arguments(), "project172", 900, 600);
            if(!graphicsProvider->isValid()) {
                e172::Debug::fatal("error: no graphics provider are valid.");
                return -1;
            }
        }
    } else if(rendererUsing == SDL) {
        graphicsProvider = new SDLGraphicsProvider(app.arguments(), "project172", 900, 600);
    } else if(rendererUsing == Console) {
        graphicsProvider = new ConsoleGraphicsProvider(app.arguments(), std::cout);
    } else {
        return 0;
    }



    SDLEventHandler eventHandler;
    SDLAudioProvider audioProvider;
    app.setEventHandler(&eventHandler);
    app.setAudioProvider(&audioProvider);
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


    app.assetProvider()->searchInFolder(app.context()->absolutePath("../assets"));
    graphicsProvider->loadFont(std::string(), app.context()->absolutePath("../assets/fonts/ZCOOL.ttf"));
    graphicsProvider->loadFont("Consolas", app.context()->absolutePath("../assets/fonts/consolas.ttf"));

    //APP INITIALIZATION CONMPLEATED

    //initialization background
    Background background = 128;
    app.addEntity(&background);

    //mem stat
    MemStatEarner memStat;
    app.addEntity(&memStat);

    //setup radar near
    Near radarNear;
    app.addEntity(&radarNear);

    //create task console
    TaskConsole taskConsole;

    taskConsole.registerTask<DockingTask>();
    taskConsole.registerTask<BuyWareTask>();
    taskConsole.registerTask<SellWareTask>();
    taskConsole.registerTask<TradeTask>();

    //setup gui
    GUIMaker guiMaker(app.context(), &radarNear, &taskConsole);
    app.addEntity(guiMaker.rootElement());

    //setup camera
    Camera camera;
    app.addEntity(&camera);
    background.bindToPhysicalObject(&camera);

    //setup world strategy
    WorldPresetStrategy worldPresetStrategy;
    worldPresetStrategy.registerType<DefaultWorld>();
    worldPresetStrategy.registerType<ArenaWorld>();
    worldPresetStrategy.registerType<HeapWorld>();
    app.addEntity(&worldPresetStrategy);

    worldPresetStrategy.controllersChanged([&guiMaker, &camera, &radarNear](const std::list<e172::ptr<Controller>> &c){
        if(c.size() > 0) {
            const auto controller = c.front();
            camera.setTarget(controller);
            guiMaker.rootElement()->setController(controller);
            radarNear.setCenter(controller);
        }
    });


    const auto presetNames = worldPresetStrategy.presetNames();
    if(presetNames.size() > 0)
        worldPresetStrategy.activatePreset(worldPresetStrategy.presetNames().front());

    guiMaker.setWorldPresetStrategy(&worldPresetStrategy);


    //independent services initialization

    ExplosiveSpawner explosiveSpawner;
    app.addEntity(&explosiveSpawner);

    app.addApplicationExtension<ScreenSettingsExtension>();
    app.addApplicationExtension<VolumeObserverExtension>();

    //debug utitlity
    ChartView chartView;

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


    chartView.setOffset({ 100, 500 });
    chartView.setFunction(f);
    chartView.setCoeficient(200);
    chartView.setPointCount(300);
    //app.addEntity(&chartView);

    //start application

    return app.exec();
}
