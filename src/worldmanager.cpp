#include "worldmanager.h"


#include "context.h"
#include "units/camera.h"
#include "gui/guicontainer.h"
#include "gui/guiradar.h"
#include "gui/guichoice.h"
#include "gui/guiswitch.h"
#include "additional/informative/registryinfo.h"
#include "additional/informative/controllerfinder.h"
#include "additional/informative/unitsamountinfo.h"
#include "state.h"
#include "additional/spm.h"
#include "additional/effects/anaglyph.h"


Camera *WorldManager::getCamera() const {
    return camera;
}

GUIMain *WorldManager::getGui() const {
    return gui;
}

void WorldManager::clear(std::vector<Worker*> *units) {
    units->clear();
}

WorldManager::WorldManager(std::vector<World *> worlds) {
    this->worlds = worlds;
    this->activeWorld = worlds[0];
}

void WorldManager::init(AssetManager *assets, std::vector<Worker*> *units, Renderer *renderer, FPSMonitor *fps, FPSMonitor *tps) {
    if(activeWorld) {
        worldIsChanged = false;
        std::vector<Controller*> players = activeWorld->generate(assets, units);
        if(players.size() > 0) {
            _near = new Near(units, players[0]);
            camera = new Camera();
            camera->setTarget(players[0]);
            units->push_back(camera);

            gui = new GUIMain(); {
                GUIStack *stack = new GUIStack(); {
                    GUIContainer *mainMenu = new GUIContainer(players[0], "main menu"); {
                        GUIContainer *infoMenu = new GUIContainer(players[0], "info menu"); {
                            infoMenu->addElement(new GUIMenuElement(players[0], std::string("\
                                \n---info---\
                                \n   --project:\
                                \n      name: project172\
                                \n      version: 0.004\
                                \n      autor: burbokop\
                                \n   --control:\
                                \n      WASD = fly\
                                \n      {\
                                \n         arrows,\
                                \n         enter,\
                                \n         backspace\
                                \n      } = menu navigation\
                                \n      space = fire\
                                \n      F = warp drive\
                            ")));
                        } mainMenu->addElement(infoMenu);
                        GUIContainer *modulesMenu = new GUIContainer(players[0], "modules"); {
                            for(Module *module : *players[0]->getParent()->getModuleHandler()->getAllModules()) {
                                modulesMenu->addElement(new GUIMenuElement(players[0], module));
                            }
                        } mainMenu->addElement(modulesMenu);
                        GUIRadar *radarMenu = new GUIRadar(players[0], "radar"); {
                            radarMenu->addArray(_near->getFocus());
                        } mainMenu->addElement(radarMenu);

                        GUIContainer *testMenu = new GUIContainer(players[0], "for developers"); {
                            testMenu->addElement(new GUIMenuElement(players[0], std::string("other players:")));
                            if(players.size() > 1) {
                                for(Controller *player : players) {
                                    if(player != players[0]) {
                                        testMenu->addElement(new GUIMenuElement(players[0], new ControllerFinder(players[0], player)));
                                    }
                                }
                            }
                            GUIContainer *worldsMenu = new GUIContainer(players[0], std::string("worlds")); {
                                unsigned long i = 0;
                                for(World* world : worlds) {
                                    worldsMenu->addElement(new GUIChoice(players[0], world->getName(), i++, std::bind(&WorldManager::onChangeReset, this, std::placeholders::_1)));
                                }
                            } testMenu->addElement(worldsMenu);
                            testMenu->addElement(new GUIMenuElement(players[0], new RegistryInfo()));
                            testMenu->addElement(new GUIMenuElement(players[0], new UnitsAmountInfo(units)));

                            testMenu->addElement(new GUIMenuElement(players[0], fps));
                            testMenu->addElement(new GUIMenuElement(players[0], tps));

                        } mainMenu->addElement(testMenu);

                        GUIContainer *optionsMenu = new GUIContainer(players[0], "options"); {
                            GUIContainer *effectsMenu = new GUIContainer(players[0], "effects"); {
                                effectsMenu->addElement(new GUISwitch(players[0], std::string("anaglyph"), std::bind(&SPM::LockEffect, new Anaglyph(Vector(10, 10))), SPM::UnlockEffect));
                            } optionsMenu->addElement(effectsMenu);
                            GUIContainer *resolutionMenu = new GUIContainer(players[0], std::string("resolution")); {
                                resolutionMenu->addElement(new GUIChoice(players[0], std::string("600x600"), Vector(600, 600), std::bind(&Renderer::setResolutionCallback, renderer, std::placeholders::_1)));
                                resolutionMenu->addElement(new GUIChoice(players[0], std::string("1360x768"), Vector(1360, 768), std::bind(&Renderer::setResolutionCallback, renderer, std::placeholders::_1)));
                                resolutionMenu->addElement(new GUIChoice(players[0], std::string("1920x1080"), Vector(1920, 1080), std::bind(&Renderer::setResolutionCallback, renderer, std::placeholders::_1)));
                            } optionsMenu->addElement(resolutionMenu);
                            optionsMenu->addElement(new GUISwitch(players[0], std::string("fullscreen"), std::bind(&Renderer::setFullscreen, renderer)));
                        } mainMenu->addElement(optionsMenu);

                        GUIContainer *stationMenu = new GUIContainer(players[0], "station"); {
                            //stationMenu->addElement(new GUIChoice());
                        } mainMenu->addElement(stationMenu);

                    } stack->push(mainMenu);
                } gui->setMenu(stack);
                gui->setMiniMap(new GUIMiniMap(players[0], units));
            }
        }
    }
}

void WorldManager::checkState(Context *context, AssetManager *assets, std::vector<Worker *> *units, Renderer *renderer, FPSMonitor *fps, FPSMonitor *tps) {
    if(worldIsChanged) {
        clear(units);
        init(assets, units, renderer, fps, tps);
        context->setGui(getGui());
        context->setNear(getNear());
        renderer->setCamera(getCamera());
    }
    _near->update();
}


Near *WorldManager::getNear() const {
    return _near;
}

void WorldManager::onChangeReset(Variant caseValue) {
    activeWorld = worlds[caseValue.toUint64()];
    worldIsChanged = true;
}
