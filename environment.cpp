#include "environment.h"

Environment::Environment() {
    this->units = new std::vector<Worker*>();
    this->assetManager = new AssetManager();
    this->context = new Context(units, assetManager);
    this->event = new Event();
}

void Environment::init() {
    resolution = new Vector(1280, 720);
    this->background = new Background(this->resolution);
    this->background->init(128);
    this->renderer = Renderer::create("project172", *resolution);
}

void Environment::start() {
    assetManager->search("./assets");
    world.init(assetManager, units);
    event->run();
    while (1) {
        Vector offset = *resolution * 0.5 - world.getCamera()->getPosition();
        background->loop(this->context, event);
        background->render(renderer, offset);
        for(unsigned long i = 0, L = units->size(); i < L; i++) {
            this->units->at(i)->loop(this->context, event);
            this->units->at(i)->render(this->renderer, offset);
        }
        renderer->update();

        if(event->getExitFlag()) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    quit();
}

void Environment::quit() {
    renderer->quit();
    event->quit();
}
