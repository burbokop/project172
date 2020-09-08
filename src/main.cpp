#include "explosivespawner.h"
#include "screensettingsextension.h"

#include <src/engine/gameapplication.h>
#include <src/engine/context.h>

#include <src/sdlimplementation/sdlaudioprovider.h>
#include <src/sdlimplementation/sdleventhandler.h>
#include <src/sdlimplementation/sdlgraphicsprovider.h>

#include <src/assetexecutors/animatorassetexecutor.h>
#include <src/assetexecutors/audioassetexecutor.h>
#include <src/assetexecutors/mapassetexecutor.h>
#include <src/assetexecutors/numberassetexecutor.h>
#include <src/assetexecutors/spriteassetexecutor.h>
#include <src/assetexecutors/stringassetexecutor.h>
#include <src/assetexecutors/vectorassetexecutor.h>

#include <src/units/particle.h>
#include <src/units/projectile.h>
#include <src/units/station.h>

#include <src/capabilities/player.h>

#include <src/capabilities/modules/engine.h>
#include <src/capabilities/modules/thruster.h>
#include <src/capabilities/modules/weapon.h>

#include <src/worlds/arenaworld.h>
#include <src/worlds/defaultworld.h>
#include <src/worlds/guimaker.h>
#include <src/worlds/heapworld.h>

#include <src/background.h>

#include <src/vulkanimplementation/vulkangraphicsprovider.h>


int main(int argc, char *argv[]) {
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
        const auto f = [&rendererUsing, &chooseGraphicsProviderApp](e172::Variant value) {
            rendererUsing = static_cast<RendererUsing>(value.toInt());
            chooseGraphicsProviderApp.quit();
        };
        menu.addMenuElement(new GUIChoice(std::string("SDL2"), SDL, f));
        menu.addMenuElement(new GUIChoice(std::string("Vulkan"), Vulkan, f));
        stack.push(&menu);
        gui.setMenu(&stack);

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
                std::cerr << "error: no graphics provider are valid.\n";
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

    app.assetProvider()->installExecutor("rate", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("interval", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("health", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("explosive", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("max-speed", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("acceleration", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("release-spead", std::make_shared<NumberAssetExecutor>());

    app.assetProvider()->installExecutor("projectile", std::make_shared<StringAssetExecutor>());

    app.assetProvider()->installExecutor("left-thrust", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("right-thrust", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("warp-speed", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("keymap", std::make_shared<MapAssetExecutor>());
    app.assetProvider()->installExecutor("damage", std::make_shared<NumberAssetExecutor>());
    app.assetProvider()->installExecutor("zoom", std::make_shared<NumberAssetExecutor>());

    app.assetProvider()->registerType<Unit>();
    app.assetProvider()->registerType<Movable>();
    app.assetProvider()->registerType<Ship>();
    app.assetProvider()->registerType<Station>();
    app.assetProvider()->registerType<Projectile>();
    app.assetProvider()->registerType<Particle>();
    app.assetProvider()->registerType<Player>();
    app.assetProvider()->registerType<Engine>();
    app.assetProvider()->registerType<Weapon>();
    app.assetProvider()->registerType<WarpDrive>();
    app.assetProvider()->registerType<Thruster>();


    app.assetProvider()->searchInFolder(app.context()->absolutePath("../assets"));
    graphicsProvider->loadFont(std::string(), app.context()->absolutePath("../assets/fonts/ZCOOL.ttf"));



    //INITIALIZATION CONMPLEATED

    //initialization background
    Background background = 128;
    app.addEntity(&background);



    //creating players
    Player *player = dynamic_cast<Player*>(app.assetProvider()->createLoadable("player1"));

    //installing armor to player

    /*
    Ship *playerArmor = dynamic_cast<Ship*>(app.assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(dynamic_cast<Module*>(app.assetProvider()->createLoadable("mini-engine")));
    playerArmorModules->addModule(dynamic_cast<Module*>(app.assetProvider()->createLoadable("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    dynamic_cast<Player*>(player)->setArmor(playerArmor);
    */

    //setting up player's ship
    Unit *playerShip = dynamic_cast<Unit*>(app.assetProvider()->createLoadable("sh1"));
    playerShip->place(e172::Vector(100, 100), -0.7);
    playerShip->addCapability(new Docker());
    playerShip->addCapability(player);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(dynamic_cast<Module*>(app.assetProvider()->createLoadable("pistol")));
    playerModuleHandler->addModule(dynamic_cast<Module*>(app.assetProvider()->createLoadable("engine2")));
    playerModuleHandler->addModule(dynamic_cast<Module*>(app.assetProvider()->createLoadable("warp-drive1")));
    playerModuleHandler->addModule(dynamic_cast<Module*>(app.assetProvider()->createLoadable("thruster1")));
    playerShip->addCapability(playerModuleHandler);
    app.addEntity(playerShip);




    //player2
    //installing armor to player2

    /*
    Ship *playerArmor2 = static_cast<Ship*>(app.assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("mini-engine")));
    playerArmorModules2->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("repair-laser")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    */

    //setup radar near
    Near radarNear(player);
    app.addEntity(&radarNear);

    //setup gui
    GUIMaker guiMaker(app.context(), &radarNear);
    guiMaker.gui()->setController(player);
    app.addEntity(guiMaker.gui());

    //setup camera
    Camera camera(player);
    app.addEntity(&camera);
    background.bindToMovable(&camera);

    //setup world strategy
    WorldPresetStrategy worldPresetStrategy;
    worldPresetStrategy.registerType<DefaultWorld>();
    worldPresetStrategy.registerType<ArenaWorld>();
    worldPresetStrategy.registerType<HeapWorld>();
    app.addEntity(&worldPresetStrategy);


    guiMaker.setWorldPresetStrategy(&worldPresetStrategy);





    //independedt services initialization

    ExplosiveSpawner explosiveSpawner;
    app.addEntity(&explosiveSpawner);

    ScreenSettingsExtension screenSettingsExtension;
    app.addApplicationExtension(&screenSettingsExtension);

    //start application

    return app.exec();
}
