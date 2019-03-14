#include "environment.h"


#include "context.h"
#include "worlds/defaultworld.h"
#include "worlds/arenaworld.h"
#include "worlds/heapworld.h"
#include "debug.h"
#include "units/camera.h"
#include "time/time.h"
#include "filesystem.h"



Environment::Environment(std::vector<std::string> args) {
    Debug::init(true, true);
    Debug::out("INIT GAME");
    Audio::init();

    units = new std::vector<Worker*>();
    assetManager = new AssetManager();
    context = new Context(units, assetManager); //tick {no}

    state = new State();
    event = new Event(); // io {no}
    netListener = new NetListener(context);

    renderer = new Renderer("project172", 600, 600, FileSystem::cutPath(args[0], 2) + "/assets/fonts/ZCOOL.ttf"); //render [no]
    background = new Background(renderer->getResolution(), 128);

    worldManager = new WorldManager({ new DefaultWorld(), new ArenaWorld(), new HeapWorld() });

    fps = new FPSMonitor("FPS:");
    tps = new FPSMonitor("TPS:");

    assetManager->search(FileSystem::cutPath(args[0], 2) + "/assets");
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
    renderer->quit();
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
