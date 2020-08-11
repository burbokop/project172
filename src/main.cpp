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


    app.assetProvider()->searchInFolder(app.context()->absolutePath("../assets"), &graphicsProvider, &audioProvider);



    WorldManager worldManager({ new DefaultWorld(), new ArenaWorld(), new HeapWorld() });

//    app.addEntity(&worldManager);

    return app.exec();
}
