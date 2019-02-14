#ifndef CONTEXT_H
#define CONTEXT_H


#include "units/particle.h"
#include "additional/lightparticle.h"

#include "assetmanager.h"

#include <queue>

#include "gui/guimain.h"
#include "gui/guicentralmessage.h"
#include "gui/guiblushingfloatingmessage.h"

#include "background.h"

struct Request {
    Worker *requester;
    Uint8 command;
    Auto argument;
};

class Context : public Object {
public:
    static const Uint8 DELETE_UNIT;
    static const Uint8 SPAWN_EXPLOSIVE;
    static const Uint8 SPAWN_UNIT;
    static const Uint8 SPAWN_SURFACE;
    static const Uint8 ADD_CAPABILITY;
    static const Uint8 REMOVE_CAPABILITY;

    static const Uint8 EMERGENCY_MESSAGE;
    static const Uint8 BACKGROUND_FLASHING;
    static const Uint8 FLOATING_MESSAGE;

private:
    std::queue<Request> eventQueue;
    std::vector<Worker*> *units;
    AssetManager *assets;

    GUIMain *gui;
    Background *background;

    void handleRequest(Request request);
public:
    Context(std::vector<Worker*> *units = nullptr, AssetManager *assets = nullptr, GUIMain *gui = nullptr);

    std::vector<Worker*> *getUnits() const;
    AssetManager *getAssets() const;

    void addEvent(Worker *requester, Uint8 command, Auto argument = Auto());

    void handleEvents();

    void setGui(GUIMain *value);
    void setBackground(Background *value);
};

#endif // CONTEXT_H
