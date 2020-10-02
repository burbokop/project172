#include "guimaker.h"


#include <src/capabilities/controller.h>
#include <src/capabilities/player.h>

#include <src/gui/guibutton.h>
#include <src/gui/guichoice.h>
#include <src/gui/guidockingview.h>
#include <src/gui/guimain.h>
#include <src/gui/guimoduleview.h>
#include <src/gui/guiradar.h>
#include <src/gui/guistringlistview.h>
#include <src/gui/guiswitch.h>
#include <src/gui/guiwareview.h>

#include <src/engine/context.h>
#include <src/engine/debug.h>
#include <src/engine/gameapplication.h>

#include <src/additional/informative/controllerfinder.h>
#include <src/additional/informative/registryinfo.h>
#include <src/additional/informative/unitsamountinfo.h>

#include <src/gui/base/guicontainer.h>


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

GUIMaker::GUIMaker(e172::Context *context, Near *radarNear) {
    m_gui = new GUIMain(); {
        GUIStack *stack = new GUIStack(); {
            GUIContainer *mainMenu = new GUIContainer("main menu"); {
                GUIContainer *infoMenu = new GUIContainer("info menu"); {
                    infoMenu->addMenuElement(new GUIMenuElement(manual));
                } mainMenu->addMenuElement(infoMenu);
                mainMenu->addMenuElement(new GUIModuleView("modules"));

                GUIDockingView *dockingView = new GUIDockingView("docking sessions");
                mainMenu->addMenuElement(dockingView);

                if(radarNear) {
                    GUIRadar *radarMenu = new GUIRadar("radar"); {
                        radarMenu->setNear(radarNear);
                        GUIContainer *radarRowElement = new GUIContainer();
                        radarRowElement->addMenuElement(new GUIButton("info", [](auto md){
                            e172::Debug::print("INFO: ", md);
                        }));
                        radarRowElement->addMenuElement(new GUIButton("select", [context](auto md){
                            context->setProperty("SU", md);
                        }));
                        radarRowElement->addMenuElement(new GUIButton("dock", [stack, dockingView](e172::Context *context, Controller* ctrl, const e172::Variant &md) {
                            e172::Debug::print("DOCK: ", md, ctrl);
                            if(const auto player = dynamic_cast<Player*>(ctrl)) {
                                if(player->dockImmediately(context, md.toNumber<e172::Entity::id_t>())) {
                                    stack->pop();
                                    stack->pop();
                                    stack->push(dockingView);
                                }
                            }
                        }));

                        radarMenu->setRowElement(radarRowElement);
                    } mainMenu->addMenuElement(radarMenu);
                }


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


                    testMenu->addMenuElement(new GUIStringListView("test static list", { "gog", "kilk", "kilk2", "end" }));

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
                        effectsMenu->addMenuElement(new GUISwitch(std::string("anaglyph"), [context]() {
                            context->emitMessage(e172::Context::CHANGE_ANAGLYPH, true);
                            //context->appliation()->renderer()->enableEffect(1);
                        }, [context]() {
                            context->emitMessage(e172::Context::CHANGE_ANAGLYPH, false);
                            //context->appliation()->renderer()->disableEffect(1);
                        }));
                    } optionsMenu->addMenuElement(effectsMenu);
                    GUIContainer *resolutionMenu = new GUIContainer(std::string("resolution")); {
                        const auto f = [context](e172::Variant value) {
                            context->emitMessage(e172::Context::CHANGE_RESOLUTION, value);
                        };
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("600x300"), e172::Vector(600, 300), f));
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("1360x768"), e172::Vector(1360, 768), f));
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("1920x1080"), e172::Vector(1920, 1080), f));
                    } optionsMenu->addMenuElement(resolutionMenu);

                    GUIContainer *fullscreenMenu = new GUIContainer(std::string("fullscreen")); {
                        const auto f = [context](e172::Variant value) {
                            context->emitMessage(e172::Context::CHANGE_FULLSCREEN, value);
                        };
                        fullscreenMenu->addMenuElement(new GUIChoice(std::string("yes"), 1, f));
                        fullscreenMenu->addMenuElement(new GUIChoice(std::string("no"), 0, f));
                    } optionsMenu->addMenuElement(fullscreenMenu);

                } mainMenu->addMenuElement(optionsMenu);

                GUIContainer *stationMenu = new GUIContainer("station"); {
                    //stationMenu->addMenuElement(new GUIChoice());
                } mainMenu->addMenuElement(stationMenu);

            } stack->push(mainMenu);
        } m_gui->addStack(stack);


        GUIStack *wareViewStack = new GUIStack(); {
            GUIWareView *wareView = new GUIWareView("storage"); {
                wareView->setTextFormat(e172::TextFormat::AlignTop | e172::TextFormat::AlignRight);

            } wareViewStack->push(wareView);
        } m_gui->addStack(wareViewStack);
        m_gui->setMiniMap(new GUIMiniMap());
        m_gui->setDebugValueInfo(new GUIDebugValueInfo());
    }
}
