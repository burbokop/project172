
#include "environment.h"


#include "worlds/defaultworld.h"
#include "worlds/arenaworld.h"
#include "worlds/heapworld.h"
#include "old_debug.h"
#include <src/units/camera.h>

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


#include <src/engine/additional.h>
#include <src/engine/context.h>

Environment::Environment(std::vector<std::string> args) {
    old::Debug::init(false, true);
    old::Debug::out("INIT GAME");

    assetManager = new e172::AssetProvider();

    assetManager->installExecutor("animation", std::make_shared<AnimatorAssetExecutor>());
    assetManager->installExecutor("sprite", std::make_shared<SpriteAssetExecutor>());
    assetManager->installExecutor("audio", std::make_shared<AudioAssetExecutor>());
    assetManager->installExecutor("offset", std::make_shared<VectorAssetExecutor>());


    assetManager->installExecutor("rate", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("interval", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("health", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("explosive", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("max-speed", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("acceleration", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("release-spead", std::make_shared<NumberAssetExecutor>());

    assetManager->installExecutor("projectile", std::make_shared<StringAssetExecutor>());

    assetManager->installExecutor("left-thrust", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("right-thrust", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("warp-speed", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("keymap", std::make_shared<MapAssetExecutor>());
    assetManager->installExecutor("damage", std::make_shared<NumberAssetExecutor>());
    assetManager->installExecutor("zoom", std::make_shared<NumberAssetExecutor>());

    assetManager->registerType<Unit>();
    assetManager->registerType<Movable>();
    assetManager->registerType<Ship>();
    assetManager->registerType<Station>();
    assetManager->registerType<Projectile>();
    assetManager->registerType<Particle>();
    assetManager->registerType<Player>();
    assetManager->registerType<Engine>();
    assetManager->registerType<Weapon>();
    assetManager->registerType<WarpDrive>();
    assetManager->registerType<Thruster>();


    eventHandler = new SDLEventHandler(); // io {no}
    netListener = new NetListener(context);

    //renderEngine = new SDLGraphicsProvider("project172", 600, 600);

    renderEngine->loadFont(std::string(), e172::Additional::absolutePath("../assets/fonts/ZCOOL.ttf", args[0]));


    renderer = renderEngine->renderer();

    background = new Background(128);


    fps = new FPSMonitor("FPS:");
    tps = new FPSMonitor("TPS:");

    std::cout << "lll: " << args[0] << "\n";

    //assetManager->search(FileSystem::cutPath(args[0], 2) + "/assets");
    assetManager->searchInFolder("../assets");

}


void Environment::start() {
    old::Debug::out("GAME STARTED");
    netListener->start();

    while (1) {
        background->proceed(this->context, eventHandler);

        for(auto e : m_entities) {
            e->proceed(context, eventHandler);
        }

        tps->count();


        //IO
        eventHandler->update();
        background->render(renderer);

        for(auto e : m_entities) {
            e->render(renderer);
        }

        fps->count();
        if(eventHandler->exitFlag()) break;
    }

    quit();
}

void Environment::quit() {
    old::Debug::out("DESTRUCTING GAME");
    netListener->quit();
    delete renderer;
    old::Debug::out("GAME STOPED");

}



/*
void Environment::gameLogicLoop() {
    while(1) {
        Time::update();
        background->proceed(this->context, event);
        background->setSpeed(worldManager->getCamera()->getVelocity());

        for(size_t i = 0, L = units->size(); i < L; i++) {
            this->units->at(i)->proceed(this->context, event);
        }

        context->handleEvents();
        worldManager->checkState(context, assetManager, units, renderer, fps, tps);

        tps->count();
        if(event->getExitFlag()) break;
    }
}

void Environment::ioLoop() {
    while(1) {
        event->loop();
        background->render(renderer);

        for(size_t i = 0, L = units->size(); i < L; i++) {
            std::cout << "io   : ( i: " << i << ", size: " << units->size() << " )\n";
            if(i < units->size()) {
                this->units->at(i)->render(this->renderer);
            }
        }

        if(GUIElement *gui = worldManager->getGui()) {
            gui->render(renderer, event);
        }

        renderer->update();

        fps->count();
        if(event->getExitFlag()) break;
    }
}
*/
