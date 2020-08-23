#include "guimaker.h"


#include <capabilities/controller.h>

#include <gui/guichoice.h>
#include <gui/guimain.h>
#include <gui/guimoduleview.h>
#include <gui/guiradar.h>
#include <gui/guiswitch.h>

#include <engine/context.h>
#include <engine/gameapplication.h>

#include <additional/informative/controllerfinder.h>
#include <additional/informative/registryinfo.h>
#include <additional/informative/unitsamountinfo.h>

#include <gui/base/guicontainer.h>


GUIMain *GUIMaker::gui() const {
    return m_gui;
}

void GUIMaker::setWorldPresetStrategy(WorldPresetStrategy *worldPresetStrategy) {
    if(m_worldComboBox) {
        m_worldComboBox->setList(worldPresetStrategy->presetNames());
        m_worldComboBox->setCallback([worldPresetStrategy](std::string world) {
            worldPresetStrategy->activatePreset(world);
        });
    }
}

GUIMaker::GUIMaker(e172::Context *context) {
    m_gui = new GUIMain(); {
        GUIStack *stack = new GUIStack(); {
            GUIContainer *mainMenu = new GUIContainer("main menu"); {
                GUIContainer *infoMenu = new GUIContainer("info menu"); {
                    infoMenu->addMenuElement(new GUIMenuElement(manual));
                } mainMenu->addMenuElement(infoMenu);
                GUIContainer *modulesMenu = new GUIModuleView("modules");
                mainMenu->addMenuElement(modulesMenu);
                //GUIRadar *radarMenu = new GUIRadar("radar"); {
                //    radarMenu->addArray(m_near->entitiesInFocus());
                //} mainMenu->addMenuElement(radarMenu);

                GUIContainer *testMenu = new GUIContainer("for developers"); {
                    testMenu->addMenuElement(new GUIMenuElement(std::string("other players:")));
                    //if(arg.controllers.size() > 1) {
                    //    for(Controller *player : arg.controllers) {
                    //        if(player != firstPlayer) {
                    //            testMenu->addMenuElement(new GUIMenuElement(new ControllerFinder(firstPlayer, player)));
                    //        }
                    //    }
                    //}
                    m_worldComboBox = new GUIComboBox<std::string>("worlds"); {
                    } testMenu->addMenuElement(m_worldComboBox);
                    testMenu->addMenuElement(new GUIMenuElement(new RegistryInfo()));
                    testMenu->addMenuElement(new GUIMenuElement(new UnitsAmountInfo(context)));

                    //if (fps){
                    //    testMenu->addMenuElement(new GUIMenuElement(fps));
                    //}
                    //if (tps){
                    //    testMenu->addMenuElement(new GUIMenuElement(tps));
                    //}


                } mainMenu->addMenuElement(testMenu);

                GUIContainer *optionsMenu = new GUIContainer("options"); {
                    GUIContainer *effectsMenu = new GUIContainer("effects"); {
                        effectsMenu->addMenuElement(new GUISwitch(std::string("anaglyph"), [context](){
                            context->emitMessage(e172::Context::CHANGE_ANAGLYPH, true);
                            //context->appliation()->renderer()->enableEffect(1);
                        }, [context]() {
                            context->emitMessage(e172::Context::CHANGE_ANAGLYPH, false);
                            //context->appliation()->renderer()->disableEffect(1);
                        }));
                    } optionsMenu->addMenuElement(effectsMenu);
                    GUIContainer *resolutionMenu = new GUIContainer(std::string("resolution")); {
                        const auto f = [context](old::Variant value) {
                            context->emitMessage(e172::Context::CHANGE_RESOLUTION, value.toVector());
                        };
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("600x600"), e172::Vector(600, 600), f));
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("1360x768"), e172::Vector(1360, 768), f));
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("1920x1080"), e172::Vector(1920, 1080), f));
                    } optionsMenu->addMenuElement(resolutionMenu);

                    GUIContainer *fullscreenMenu = new GUIContainer(std::string("fullscreen")); {
                        const auto f = [context](old::Variant value){
                            context->emitMessage(e172::Context::CHANGE_FULLSCREEN, value.toInt32());
                        };
                        fullscreenMenu->addMenuElement(new GUIChoice(std::string("yes"), 1, f));
                        fullscreenMenu->addMenuElement(new GUIChoice(std::string("no"), 0, f));
                    } optionsMenu->addMenuElement(fullscreenMenu);

                } mainMenu->addMenuElement(optionsMenu);

                GUIContainer *stationMenu = new GUIContainer("station"); {
                    //stationMenu->addMenuElement(new GUIChoice());
                } mainMenu->addMenuElement(stationMenu);

            } stack->push(mainMenu);
        } m_gui->setMenu(stack);
        m_gui->setMiniMap(new GUIMiniMap());
        m_gui->setDebugValueInfo(new GUIDebugValueInfo());
    }
}
