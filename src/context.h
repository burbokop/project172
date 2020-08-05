#ifndef CONTEXT_H
#define CONTEXT_H

#include <queue>


#include "assetmanager.h"
#include "gui/guimain.h"
#include "near.h"
#include "background.h"


struct Request {
    Worker *requester;
    unsigned command;
    Variant argument;
};

class Context : public Object {
public:
    static const unsigned DELETE_UNIT;
    static const unsigned SPAWN_EXPLOSIVE;
    static const unsigned SPAWN_ENGINE_EXPLOSIVE;
    static const unsigned SPAWN_ENGINE_PARTICLES;
    static const unsigned SPAWN_UNIT;
    static const unsigned SPAWN_SURFACE;
    static const unsigned ADD_CAPABILITY;
    static const unsigned REMOVE_CAPABILITY;

    static const unsigned EMERGENCY_MESSAGE;
    static const unsigned BACKGROUND_FLASHING;
    static const unsigned FLOATING_MESSAGE;

private:
    std::queue<Request> eventQueue;
    std::vector<Worker*> *units;

    AssetManager *assets;

    GUIMain *gui = nullptr;
    Background *background = nullptr;
    Near *_near = nullptr;

    void handleRequest(Request request);
public:
    Context(std::vector<Worker*> *units = nullptr, AssetManager *assets = nullptr, GUIMain *gui = nullptr);

    std::vector<Worker*> *getUnits() const;
    AssetManager *getAssets() const;

    void addEvent(Worker *requester, unsigned command, Variant argument = Variant());

    void handleEvents();

    void setGui(GUIMain *value);
    void setBackground(Background *value);
    void setNear(Near *value);
};

#endif // CONTEXT_H
