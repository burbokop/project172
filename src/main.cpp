#include "explosivespawner.h"
#include "appextensions/screensettingsextension.h"

#include <src/gameapplication.h>
#include <src/context.h>
#include <src/debug.h>
#include <src/additional.h>
#include <src/testprovider.h>

#include <src/sdlaudioprovider.h>
#include <src/sdleventhandler.h>
#include <src/sdlgraphicsprovider.h>


#include <src/assetexecutors/animatorassetexecutor.h>
#include <src/assetexecutors/audioassetexecutor.h>
#include <src/assetexecutors/factoryassetexecutor.h>
#include <src/assetexecutors/spriteassetexecutor.h>
#include <src/assetexecutors/vectorassetexecutor.h>

#include <src/capabilities/factory.h>
#include <src/capabilities/player.h>

#include <src/worlds/arenaworld.h>
#include <src/worlds/defaultworld.h>
#include <src/worlds/guimaker.h>
#include <src/worlds/heapworld.h>

#include <src/background.h>

#include <src/vulkanimplementation/vulkangraphicsprovider.h>

#include <tests/waretest.h>
#include <src/additional/chartview.h>
#include <src/additional/memstatearner.h>
#include <src/gui/guibutton.h>
#include <src/gui/base/guicontainer.h>
#include <src/units/projectile.h>
#include <src/units/ship.h>
#include <src/units/station.h>
#include <src/capabilities/modules/engine.h>
#include <src/capabilities/modules/thruster.h>
#include <src/capabilities/modules/warpdrive.h>
#include <src/capabilities/modules/weapon.h>
#include <src/appextensions/volumeobserverextension.h>

extern "C" {
int go_run_server();
void go_stop_service(int);
void go_http_get();
}

//import test_module;  // import declaration

int main(int argc, char *argv[]) {
    //hello();


    //const int desc = go_run_server();
    //go_stop_service(desc);
    //go_http_get();

    //TestProvider::runAllTests();

    //if constexpr(false) {
    //    size_t sum = 0;
    //    for(size_t i = 0; i < 100; ++i) {
    //        const auto s = e172::Variant::testSpeed();
    //        std::cout << "[" << i << "%] e172::Variant::testSpeed: " << s << "\n";
    //        sum += s;
    //    }
    //    std::cout << "e172::Variant::testSpeed (average): " << sum / 100 << "\n";
    //    for(size_t i = 0; i < 10; ++i) {
    //        const auto a = e172::Variant::testSpeed(1000000);
    //        std::cout << "[" << (i * 10) << "%] e172::Variant::testSpeed(1000000): " << a.first << " : " << a.second << "\n";
    //    }
    //}


    enum RendererUsing {
        Undefined,
        SDL,
        Vulkan
    };
    RendererUsing rendererUsing = Undefined;
    {
        e172::GameApplication chooseGraphicsProviderApp(argc, argv);
        SDLGraphicsProvider gprovider(chooseGraphicsProviderApp.arguments(), "choose gprovider", 108, 148);
        SDLEventHandler eventHandler;
        chooseGraphicsProviderApp.setGraphicsProvider(&gprovider);
        chooseGraphicsProviderApp.setEventHandler(&eventHandler);

        Background background = 32;
        chooseGraphicsProviderApp.addEntity(&background);

        GUIMain gui;
        GUIStack stack;
        GUIContainer menu("renderer");
        const auto apply = [&rendererUsing, &chooseGraphicsProviderApp](e172::Variant value) {
            rendererUsing = static_cast<RendererUsing>(value.toInt());
            chooseGraphicsProviderApp.quit();
        };
        menu.addMenuElement(new GUIButton(std::string("SDL2"), [apply](auto) { apply(SDL); }));
        menu.addMenuElement(new GUIButton(std::string("Vulkan"), [apply](auto) { apply(Vulkan); }));
        stack.push(&menu);
        gui.addStack(&stack);

        gprovider.loadFont(std::string(), chooseGraphicsProviderApp.context()->absolutePath("../assets/fonts/ZCOOL.ttf"));

        chooseGraphicsProviderApp.addEntity(&gui);
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
    } else {
        return 0;
    }



    SDLEventHandler eventHandler;
    SDLAudioProvider audioProvider;
    app.setEventHandler(&eventHandler);
    app.setAudioProvider(&audioProvider);
    app.setGraphicsProvider(graphicsProvider);

    app.assetProvider()->installExecutor("animation", std::make_shared<AnimatorAssetExecutor>());
    app.assetProvider()->installExecutor("sprite", std::make_shared<SpriteAssetExecutor>());
    app.assetProvider()->installExecutor("audio", std::make_shared<AudioAssetExecutor>());
    app.assetProvider()->installExecutor("offset", std::make_shared<VectorAssetExecutor>());
    app.assetProvider()->installExecutor("input", std::make_shared<RecieptAssetExecutor>());
    app.assetProvider()->installExecutor("output", std::make_shared<RecieptAssetExecutor>());

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


    app.assetProvider()->searchInFolder(app.context()->absolutePath("../assets"));
    graphicsProvider->loadFont(std::string(), app.context()->absolutePath("../assets/fonts/ZCOOL.ttf"));

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

    //setup gui
    GUIMaker guiMaker(app.context(), &radarNear);
    app.addEntity(guiMaker.gui());

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

    worldPresetStrategy.controllersChanged([&guiMaker, &camera, &radarNear](auto c){
        if(c.size() > 0) {
            const auto controller = c.front();
            camera.setTarget(controller);
            guiMaker.gui()->setController(controller);
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
