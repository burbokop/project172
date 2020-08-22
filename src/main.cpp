#include <iostream>
#include <locale>


#include <engine/gameapplication.h>
#include <engine/context.h>

#include <sdlimplementation/sdlaudioprovider.h>
#include <sdlimplementation/sdleventhandler.h>
#include <sdlimplementation/sdlgraphicsprovider.h>

#include <assetexecutors/animatorassetexecutor.h>
#include <assetexecutors/audioassetexecutor.h>
#include <assetexecutors/mapassetexecutor.h>
#include <assetexecutors/numberassetexecutor.h>
#include <assetexecutors/spriteassetexecutor.h>
#include <assetexecutors/stringassetexecutor.h>
#include <assetexecutors/vectorassetexecutor.h>

#include <units/particle.h>
#include <units/projectile.h>
#include <units/station.h>

#include <capabilities/player.h>

#include <capabilities/modules/engine.h>
#include <capabilities/modules/thruster.h>
#include <capabilities/modules/weapon.h>

#include <worlds/arenaworld.h>
#include <worlds/defaultworld.h>
#include <worlds/guisetup.h>
#include <worlds/heapworld.h>


#include "environment.h"


int main(int argc, char *argv[]) {
    e172::GameApplication app(argc, argv);
    SDLEventHandler eventHandle;
    SDLAudioProvider audioProvider;
    SDLGraphicsProvider graphicsProvider("project172", 900, 600);

    app.setEventHandler(&eventHandle);
    app.setAudioProvider(&audioProvider);
    app.setGraphicsProvider(&graphicsProvider);

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
    graphicsProvider.loadFont(std::string(), app.context()->absolutePath("../assets/fonts/ZCOOL.ttf"));



    //INITIALIZATION CONMPLEATED


    Background background = 128;
    app.addEntity(&background);





    //player1
    Player *player1 = static_cast<Player*>(app.assetProvider()->createLoadable("player1"));
    Ship *playerArmor = static_cast<Ship*>(app.assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("mini-engine")));
    playerArmorModules->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);

    Unit *playerShip = static_cast<Unit*>(app.assetProvider()->createLoadable("sh1"));
    playerShip->place(e172::Vector(100, 100), -0.7);

    playerShip->addCapability(new Docker());
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("warp-drive1")));
    playerModuleHandler->addModule(static_cast<Module*>(app.assetProvider()->createLoadable("thruster1")));
    playerShip->addCapability(playerModuleHandler);

    app.addEntity(playerShip);

    GuiSetup guiSetup(app.context());
    guiSetup.gui()->setController(player1);
    app.addEntity(guiSetup.gui());

    //GUIContainer container("ggg");
    //
    //GUIMenuElement menu_e("gogadoda");
    //container.addMenuElement(&menu_e);
    //GUIMenuElement menu_e2("kilikili");
    //container.addMenuElement(&menu_e2);
    //
    //app.addEntity(&container);


    WorldPresetStrategy worldPresetStrategy;
    worldPresetStrategy.registerType<DefaultWorld>();
    worldPresetStrategy.registerType<ArenaWorld>();
    worldPresetStrategy.registerType<HeapWorld>();
    app.addEntity(&worldPresetStrategy);





    return app.exec();
}
