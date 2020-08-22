#include "guisetup.h"


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


GUIMain *GuiSetup::gui() const {
    return m_gui;
}

GuiSetup::GuiSetup(e172::Context *context) {    
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
                    GUIContainer *worldsMenu = new GUIContainer(std::string("worlds")); {
                        unsigned long i = 0;
                        //for(WorldPreset* world : worlds) {
                        //    worldsMenu->addMenuElement(new GUIChoice(world->getName(), i++, std::bind(&PresetStrategy::onChangeReset, this, std::placeholders::_1)));
                        //}
                    } testMenu->addMenuElement(worldsMenu);
                    testMenu->addMenuElement(new GUIMenuElement(new RegistryInfo()));
                    testMenu->addMenuElement(new GUIMenuElement(new UnitsAmountInfo(context->entities())));

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
                            context->appliation()->renderer()->enableEffect(1);
                        }, [context](){
                            context->appliation()->renderer()->disableEffect(1);
                        }));
                    } optionsMenu->addMenuElement(effectsMenu);
                    GUIContainer *resolutionMenu = new GUIContainer(std::string("resolution")); {
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("600x600"), e172::Vector(600, 600), std::bind(&e172::AbstractRenderer::setResolutionCallback, context->appliation()->renderer(), std::placeholders::_1)));
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("1360x768"), e172::Vector(1360, 768), std::bind(&e172::AbstractRenderer::setResolutionCallback, context->appliation()->renderer(), std::placeholders::_1)));
                        resolutionMenu->addMenuElement(new GUIChoice(std::string("1920x1080"), e172::Vector(1920, 1080), std::bind(&e172::AbstractRenderer::setResolutionCallback, context->appliation()->renderer(), std::placeholders::_1)));
                    } optionsMenu->addMenuElement(resolutionMenu);
                    optionsMenu->addMenuElement(new GUISwitch(std::string("fullscreen"), std::bind(&e172::AbstractRenderer::setFullscreen, context->appliation()->renderer())));
                } mainMenu->addMenuElement(optionsMenu);

                GUIContainer *stationMenu = new GUIContainer("station"); {
                    //stationMenu->addMenuElement(new GUIChoice());
                } mainMenu->addMenuElement(stationMenu);

            } stack->push(mainMenu);
        } m_gui->setMenu(stack);
        m_gui->setMiniMap(new GUIMiniMap(context->entities()));
        m_gui->setDebugValueInfo(new GUIDebugValueInfo(context->entities()));
    }

}
