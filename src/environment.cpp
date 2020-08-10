
#include "environment.h"


#include "context.h"
#include "worlds/defaultworld.h"
#include "worlds/arenaworld.h"
#include "worlds/heapworld.h"
#include "debug.h"
#include "units/camera.h"
#include "time/time.h"
#include "filesystem.h"

#include <sdlimplementation/sdlaudioprovider.h>
#include <sdlimplementation/sdlgraphicsprovider.h>

#include <assettools/assetexecutors/animatorassetexecutor.h>
#include <assettools/assetexecutors/audioassetexecutor.h>
#include <assettools/assetexecutors/mapassetexecutor.h>
#include <assettools/assetexecutors/numberassetexecutor.h>
#include <assettools/assetexecutors/spriteassetexecutor.h>
#include <assettools/assetexecutors/stringassetexecutor.h>
#include <assettools/assetexecutors/vectorassetexecutor.h>

#include <units/particle.h>
#include <units/projectile.h>
#include <units/station.h>

#include <capabilities/player.h>

#include <capabilities/modules/engine.h>
#include <capabilities/modules/thruster.h>
#include <capabilities/modules/weapon.h>

#include "audio/audio.h"

#include <engine/additional.h>

Environment::Environment(std::vector<std::string> args) {
    Debug::init(false, true);
    Debug::out("INIT GAME");
    Audio::init();

    units = new std::vector<Worker*>();
    assetManager = new AssetProvider();

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


    context = new Context(units, assetManager); //tick {no}

    state = new State();
    event = new Event(); // io {no}
    netListener = new NetListener(context);

    renderEngine = new SDLGraphicsProvider("project172", 600, 600);

    renderEngine->loadFont(std::string(), e172::Additional::absolutePath("../assets/fonts/ZCOOL.ttf", args[0]));

    auto audioProvider = new SDLAudioProvider();

    renderer = renderEngine->renderer();

    background = new Background(renderer->resolution(), 128);

    worldManager = new WorldManager({ new DefaultWorld(), new ArenaWorld(), new HeapWorld() });

    fps = new FPSMonitor("FPS:");
    tps = new FPSMonitor("TPS:");

    std::cout << "lll: " << args[0] << "\n";

    //assetManager->search(FileSystem::cutPath(args[0], 2) + "/assets");
    assetManager->searchInFolder("../assets", renderEngine, audioProvider);

    worldManager->checkState(context, assetManager, units, renderer, fps, tps);
    context->setBackground(background);
}


void Environment::start() {
    Debug::out("GAME STARTED");
    netListener->start();

    while (1) {
        Time::update();
        background->tick(this->context, event);
        background->setSpeed(worldManager->getCamera()->getVelocity());

        for(size_t i = 0, L = units->size(); i < L; i++) {
            this->units->at(i)->tick(this->context, event);
        }

        context->handleEvents();
        worldManager->checkState(context, assetManager, units, renderer, fps, tps);

        tps->count();

        //IO
        event->loop();
        background->render(renderer);

        for(size_t i = 0, L = units->size(); i < L; i++) {
            this->units->at(i)->render(this->renderer);
        }

        if(GUIElement *gui = worldManager->getGui()) {
            gui->tick(context, event);
            gui->render(renderer);
        }

        renderer->update();

        event->unpressAll();

        fps->count();
        if(event->getExitFlag()) break;
    }

    quit();
}

void Environment::quit() {
    Debug::out("DESTRUCTING GAME");
    netListener->quit();
    delete renderer;
    event->quit();
    Debug::out("GAME STOPED");
}



/*
void Environment::gameLogicLoop() {
    while(1) {
        Time::update();
        background->tick(this->context, event);
        background->setSpeed(worldManager->getCamera()->getVelocity());

        for(size_t i = 0, L = units->size(); i < L; i++) {
            this->units->at(i)->tick(this->context, event);
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
