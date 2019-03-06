#include "environment.h"


#include "context.h"
#include "worlds/defaultworld.h"
#include "worlds/arenaworld.h"
#include "worlds/heapworld.h"
#include "debug.h"
#include "units/camera.h"




Environment::Environment() {
    this->state = new State();
    this->units = new std::vector<Worker*>();
    this->assetManager = new AssetManager();
    this->context = new Context(units, assetManager);
    this->event = new Event();
    this->fps = new FPSMonitor();
    this->netListener = new NetListener(context);
    this->worldManager = new WorldManager({ new DefaultWorld(), new ArenaWorld(), new HeapWorld() });
    this->background = new Background();
}

void Environment::init(int argc, char *argv[]) {
    Debug::out("INIT GAME");
    this->renderer = Renderer::create("project172", 600, 600, "../assets/fonts/ZCOOL.ttf");
    Audio::init();
    assetManager->search("../assets");
    if(argc > 1) this->background->init(this->renderer->getResolution(), 128, std::stod(argv[1]));
    else this->background->init(this->renderer->getResolution(), 128);
    worldManager->checkState(context, assetManager, units, renderer, fps);
    context->setBackground(background);
}

void Environment::start() {
    Debug::out("GAME STARTED");
    netListener->start();
    Timer loopTimer = Timer(1000 / state->getMaxFPS());
    loopTimer.reset();

    while(1) {
        event->loop();
        background->loop(this->context, event);
        background->setSpeed(worldManager->getCamera()->getVelocity());
        background->render(renderer);
        for(unsigned long long i = 0, L = units->size(); i < L; i++) {
            this->units->at(i)->loop(this->context, event);
            this->units->at(i)->render(this->renderer);
        }

        GUIElement *gui = worldManager->getGui();
        if(gui != nullptr) {
            gui->update();
            gui->render(renderer, event);
        }
        renderer->update();
        context->handleEvents();
        worldManager->checkState(context, assetManager, units, renderer, fps);
        if(event->getExitFlag()) break;
        fps->count();

        if(State::getLoopBehaviour() == State::TIMER) {
            while (!loopTimer.count()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(fps->toUint32() * 1000 / static_cast<long long>(std::pow(State::getMaxFPS(), 2))));
        }
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
