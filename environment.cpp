#include "environment.h"

Environment::Environment() {
    this->state = new State();
    this->units = new std::vector<Worker*>();
    this->assetManager = new AssetManager();
    this->context = new Context(units, assetManager);
    this->event = new Event();
    this->fps = new FPSMonitor();
    this->netListener = new NetListener(context);
    this->worldManager = new WorldManager({ new DefaultWorld(), new ArenaWorld() });
}

void Environment::init(int argc, char *argv[]) {
    this->renderer = Renderer::create("project172", 600, 600, "./assets/fonts/ZCOOL.ttf");
    this->background = new Background();
    if(argc > 1) this->background->init(this->renderer->getResolution(), 128, std::stod(argv[1]));
    else this->background->init(this->renderer->getResolution(), 128);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Debug::init();
}

//---test
void Environment::logic() {

}
//---

void Environment::start() {
    assetManager->search("./assets");
    worldManager->init(context, assetManager, units, renderer, fps);
    context->setBackground(background);

    //test---
    std::thread logicThread(&Environment::logic, this);
    //-------

    netListener->start();
    while (1) {
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
        std::this_thread::sleep_for(std::chrono::milliseconds(fps->toUint32() * 1000 / static_cast<long long>(std::pow(state->getMaxFPS(), 2))));
    }
    quit();
}

void Environment::quit() {
    netListener->quit();
    renderer->quit();
    event->quit();
}
