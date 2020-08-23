
#include "environment.h"


#include "worlds/defaultworld.h"
#include "worlds/arenaworld.h"
#include "worlds/heapworld.h"
#include "debug.h"
#include "units/camera.h"
#include "filesystem.h"

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


#include <engine/additional.h>
#include <engine/context.h>

Environment::Environment(std::vector<std::string> args) {
    Debug::init(false, true);
    Debug::out("INIT GAME");

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


    context = new e172::Context(&m_entities, assetManager); //proceed {no}

    state = new State();
    eventHandler = new SDLEventHandler(); // io {no}
    netListener = new NetListener(context);

    renderEngine = new SDLGraphicsProvider("project172", 600, 600);

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
    Debug::out("GAME STARTED");
    netListener->start();

    while (1) {
        background->proceed(this->context, eventHandler);

        for(auto e : m_entities) {
            e->proceed(context, eventHandler);
        }

        context->handleEvents();

        tps->count();

        //IO
        eventHandler->update();
        background->render(renderer);

        for(auto e : m_entities) {
            e->render(renderer);
        }

        renderer->update();

        fps->count();
        if(eventHandler->exitFlag()) break;
    }

    quit();
}

void Environment::quit() {
    Debug::out("DESTRUCTING GAME");
    netListener->quit();
    delete renderer;
    Debug::out("GAME STOPED");
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
