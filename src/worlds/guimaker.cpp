#include "guimaker.h"
#include "src/messagetype.h"

#include <src/capabilities/controller.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/player.h>
#include <src/capabilities/warestorage.h>

#include <src/gui/guibutton.h>
#include <src/gui/guidebugvalueinfo.h>
#include <src/gui/guiconsole.h>
#include <src/gui/guidockingview.h>
#include <src/gui/guifloatingmessagecontainer.h>
#include <src/gui/guiminimap.h>
#include <src/gui/guimoduleview.h>
#include <src/gui/guiradar.h>
#include <src/gui/guistringlistview.h>
#include <src/gui/guiswitch.h>
#include <src/gui/guiwareview.h>

#include <src/units/unit.h>
#include <src/context.h>
#include <src/debug.h>
#include <src/gameapplication.h>
#include <src/capabilities/docker.h>
#include <src/additional/informative/controllerfinder.h>
#include <src/additional/informative/unitsamountinfo.h>

#include <e172/src/functional/metafunction.h>
#include <src/gui/base/guicontainer.h>
#include <src/gui/base/guifocusswitch.h>
#include <src/gui/base/guimenu.h>

namespace proj172::core {

void GUIMaker::setWorldPresetStrategy(WorldPresetStrategy *worldPresetStrategy)
{
    if(m_worldComboBox) {
        m_worldComboBox->setList(worldPresetStrategy->presetNames());
        m_worldComboBox->setCallback([worldPresetStrategy](std::string world) {
            worldPresetStrategy->activatePreset(world);
        });
    }
}

e172::ptr<GUIElement> GUIMaker::rootElement() const {
    return m_rootElement;
}

GUIMaker::GUIMaker(e172::Context *context,
                   Near *radarNear,
                   const std::shared_ptr<TaskConsole> &console)
{
    m_rootElement = e172::FactoryMeta::make<GUIContainer>();
    {
        auto menuFocusSwitch = e172::FactoryMeta::make<GUIFocusSwitch>(e172::ScancodeLeft,
                                                                       e172::ScancodeRight);
        {
            auto stack = e172::FactoryMeta::make<GUIStack>();
            {
                auto mainMenu = e172::FactoryMeta::make<GUIMenu>("main menu");
                {
                    auto infoMenu = e172::FactoryMeta::make<GUIMenu>("info menu");
                    {
                        infoMenu->addMenuElement(e172::FactoryMeta::make<GUIMenuElement>(manual));
                    }
                    mainMenu->addMenuElement(infoMenu);
                    mainMenu->addMenuElement(e172::FactoryMeta::make<GUIModuleView>("modules"));

                    auto dockingView = e172::FactoryMeta::make<GUIDockingView>("docking sessions");
                    {
                        auto dockingViewRowElement = e172::FactoryMeta::make<GUIMenu>();
                        {
                            auto dockingWareView = e172::FactoryMeta::make<GUIWareView>("storage");
                            {
                                dockingWareView->setUnitProvider([this](const e172::ptr<Controller>& controller, const e172::Variant &modelData){
                                    if(auto parent = controller->parentUnit()) {
                                        if(auto docker = parent->capability<Docker>()) {
                                            if(docker->docked(modelData.toSize_t())) {
                                                m_currentOppositeUnit = docker->oppositeUnit(modelData.toSize_t());
                                                return m_currentOppositeUnit;
                                            }
                                        }
                                    }
                                    return e172::ptr<Unit>();
                                });
                                auto dockingWareViewButton = e172::FactoryMeta::make<GUIButton>(
                                    "",
                                    [](const e172::ptr<Controller> &ctrl, const e172::Variant &md) {
                                        md.fold<WareStorage::WareRef>(
                                            [ctrl](const WareStorage::WareRef &ref) {
                                                if (auto parent = ctrl->parentUnit()) {
                                                    if (auto parentStorage
                                                        = parent->capability<WareStorage>()) {
                                                        auto c = ref.storage()
                                                                     ->transferWareTo(ref.index(),
                                                                                      parentStorage,
                                                                                      1);
                                                    }
                                                }
                                            });
                                    });
                                {}
                                dockingWareView->setRowElement(dockingWareViewButton);
                            }
                            dockingViewRowElement->addMenuElement(dockingWareView);
                        }
                        dockingView->setRowElement(dockingViewRowElement);
                    }
                    mainMenu->addMenuElement(dockingView);

                    if(radarNear) {
                        GUIRadar *radarMenu = e172::FactoryMeta::make<GUIRadar>("radar");
                        {
                            radarMenu->setNear(radarNear);
                            auto radarRowElement = e172::FactoryMeta::make<GUIMenu>();
                            radarRowElement->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>("info", [](auto md) {
                                    e172::Debug::print("INFO: ", md);
                                }));
                            radarRowElement->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>("select", [context](auto md) {
                                    context->setProperty("SU", md);
                                }));
                            radarRowElement->addMenuElement(e172::FactoryMeta::make<GUIButton>(
                                "dock",
                                [stack, dockingView](e172::Context *context,
                                                     const e172::ptr<Controller> &ctrl,
                                                     const e172::Variant &md) {
                                    e172::Debug::print("DOCK: ", md, ctrl);
                                    if (const auto player = e172::smart_cast<Player>(ctrl)) {
                                        if (player->createDockingSessionWithUnit(
                                                context, md.toNumber<e172::Entity::Id>())) {
                                            stack->pop();
                                            stack->pop();
                                            stack->push(dockingView);
                                        }
                                    }
                                }));

                            radarMenu->setRowElement(radarRowElement);
                        }
                        mainMenu->addMenuElement(radarMenu);
                    }

                    auto testMenu = e172::FactoryMeta::make<GUIMenu>("for developers");
                    {
                        testMenu->addMenuElement(
                            e172::FactoryMeta::make<GUIMenuElement>(std::string("other players:")));
                        //if(arg.controllers.size() > 1) {
                        //    for(Controller *player : arg.controllers) {
                        //        if(player != firstPlayer) {
                        //            testMenu->addMenuElement(new GUIMenuElement(new ControllerFinder(firstPlayer, player)));
                        //        }
                        //    }
                        //}
                        m_worldComboBox = e172::FactoryMeta::make<GUIComboBox<std::string>>(
                            "worlds");
                        {}
                        testMenu->addMenuElement(m_worldComboBox);

                        testMenu->addMenuElement(e172::FactoryMeta::make<GUIStringListView>(
                            "test static list",
                            std::vector<std::string>{"gog", "kilk", "kilk2", "end"}));
                        testMenu->addMenuElement(
                            e172::FactoryMeta::make<GUIMenuElement>(new UnitsAmountInfo(context)));

                        //if (fps){
                        //    testMenu->addMenuElement(new GUIMenuElement(fps));
                        //}
                        //if (tps){
                        //    testMenu->addMenuElement(new GUIMenuElement(tps));
                        //}
                    }
                    mainMenu->addMenuElement(testMenu);

                    auto optionsMenu = e172::FactoryMeta::make<GUIMenu>("options");
                    {
                        auto effectsMenu = e172::FactoryMeta::make<GUIMenu>("effects");
                        {
                            effectsMenu->addMenuElement(e172::FactoryMeta::make<GUISwitch>(
                                std::string("anaglyph"),
                                [context]() {
                                    context->emitMessage(~MessageType::ChangeAnaglyph, true);
                                    //context->appliation()->renderer()->enableEffect(1);
                                },
                                [context]() {
                                    context->emitMessage(~MessageType::ChangeAnaglyph, false);
                                }));
                        }
                        optionsMenu->addMenuElement(effectsMenu);
                        auto resolutionMenu = e172::FactoryMeta::make<GUIMenu>(
                            std::string("resolution"));
                        {
                            const auto setResolution = [context](e172::Vector<double> value) {
                                context->emitMessage(~MessageType::ChangeResolution, value);
                            };
                            resolutionMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("600x300"),
                                                                   [setResolution](auto) {
                                                                       setResolution({600, 300});
                                                                   }));
                            resolutionMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("1360x768"),
                                                                   [setResolution](auto) {
                                                                       setResolution({1360, 768});
                                                                   }));
                            resolutionMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("1920x1080"),
                                                                   [setResolution](auto) {
                                                                       setResolution({1920, 1080});
                                                                   }));
                        }
                        optionsMenu->addMenuElement(resolutionMenu);

                        auto fullscreenMenu = e172::FactoryMeta::make<GUIMenu>(
                            std::string("fullscreen"));
                        {
                            const auto setFullscreen = [context](e172::Variant value) {
                                context->emitMessage(~MessageType::ChangeFullscreen, value);
                            };
                            fullscreenMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("yes"),
                                                                   [setFullscreen](auto) {
                                                                       setFullscreen(1);
                                                                   }));
                            fullscreenMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("no"),
                                                                   [setFullscreen](auto) {
                                                                       setFullscreen(0);
                                                                   }));
                        }
                        optionsMenu->addMenuElement(fullscreenMenu);

                        auto volumeMenu = e172::FactoryMeta::make<GUIMenu>(std::string("volume"));
                        {
                            const auto setVolume = [context](double value) {
                                context->setSettingValue("general_volume", value);
                            };
                            volumeMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("000%"),
                                                                   [setVolume](auto) {
                                                                       setVolume(0);
                                                                   }));
                            volumeMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("025%"),
                                                                   [setVolume](auto) {
                                                                       setVolume(0.25);
                                                                   }));
                            volumeMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("050%"),
                                                                   [setVolume](auto) {
                                                                       setVolume(0.5);
                                                                   }));
                            volumeMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("075%"),
                                                                   [setVolume](auto) {
                                                                       setVolume(0.75);
                                                                   }));
                            volumeMenu->addMenuElement(
                                e172::FactoryMeta::make<GUIButton>(std::string("100%"),
                                                                   [setVolume](auto) {
                                                                       setVolume(1);
                                                                   }));
                        }
                        optionsMenu->addMenuElement(volumeMenu);
                    }
                    mainMenu->addMenuElement(optionsMenu);

                    auto stationMenu = e172::FactoryMeta::make<GUIMenu>("station");
                    {
                        //stationMenu->addMenuElement(new GUIChoice());
                    }
                    mainMenu->addMenuElement(stationMenu);
                }
                stack->push(mainMenu);
            }
            menuFocusSwitch->addChildElement(stack);

            GUIStack *wareViewStack = e172::FactoryMeta::make<GUIStack>();
            {
                GUIWareView *wareView = e172::FactoryMeta::make<GUIWareView>("storage");
                {
                    wareView->setTextFormat(e172::TextFormat::AlignTop | e172::TextFormat::AlignRight);
                    auto wareViewButton = e172::FactoryMeta::make<GUIButton>(
                        "", [this](const e172::ptr<Controller> &ctrl, const e172::Variant &md) {
                            md.fold<WareStorage::WareRef>(
                                [ctrl, this](const WareStorage::WareRef &ref) {
                                    if (m_currentOppositeUnit) {
                                        if (auto oppositeStorage
                                            = m_currentOppositeUnit->capability<WareStorage>()) {
                                            ref.storage()->transferWareTo(ref.index(),
                                                                          oppositeStorage,
                                                                          1);
                                        }
                                    }
                                });
                        });
                    {}
                    wareView->setRowElement(wareViewButton);
                }
                wareViewStack->push(wareView);
            }
            menuFocusSwitch->addChildElement(wareViewStack);
        }
        m_rootElement->addChildElement(menuFocusSwitch);

        if (console) {
            m_rootElement->addChildElement(e172::FactoryMeta::make<GuiConsole>(
                [console](const std::string &c, e172::ClosableOutputStream &s, e172::Context *ctx) {
                    console->executeCommand(c, s, ctx);
                },
                [console]() -> std::list<std::string> { return console->compleateVariants(); }));
        }
        m_rootElement->addChildElement(e172::FactoryMeta::make<GUIMiniMap>());
        m_rootElement->addChildElement(e172::FactoryMeta::make<GUIDebugValueInfo>());

        m_rootElement->addChildElement(e172::FactoryMeta::make<GUIFloatingMessageContainer>());
    }
}

} // namespace proj172::core
