#include "renderlayer.h"

#include "background.h"
#include "gui/base/guicontainer.h"
#include "gui/base/guimenu.h"
#include "gui/base/guistack.h"
#include "gui/guibutton.h"
#include <e172/context.h>
#include <e172/debug.h>
#include <e172/gameapplication.h>
#include <e172/impl/console/graphicsprovider.h>
#include <e172/impl/sdl/eventprovider.h>
#include <e172/impl/sdl/graphicsprovider.h>
#include <e172/impl/vulkan/graphicsprovider.h>
#include <iostream>

namespace proj172 {

namespace {

enum RenderLayer { Undefined, SDL, Vulkan, Console };

RenderLayer chooseRenderLayer(const std::vector<std::string> &args)
{
    using namespace proj172::core;
    RenderLayer result = Undefined;
    {
        e172::GameApplication chooseGraphicsProviderApp(args);
        const auto gprovider = std::make_shared<e172::impl::sdl::GraphicsProvider>(
            chooseGraphicsProviderApp.arguments(),
            "choose gprovider",
            e172::Vector<std::uint32_t>{118, 168});
        const auto eventProvider = std::make_shared<e172::impl::sdl::EventProvider>();
        chooseGraphicsProviderApp.setGraphicsProvider(gprovider);
        chooseGraphicsProviderApp.setEventProvider(eventProvider);

        const auto background = e172::FactoryMeta::makeUniq<Background>(32);
        chooseGraphicsProviderApp.addEntity(background.get());

        const auto rootElement = e172::FactoryMeta::makeUniq<GUIContainer>();
        const auto stack = e172::FactoryMeta::makeUniq<GUIStack>();
        const auto menu = e172::FactoryMeta::makeUniq<GUIMenu>("renderer");
        const auto apply = [&result, &chooseGraphicsProviderApp](e172::Variant value) {
            result = static_cast<RenderLayer>(value.toInt());
            chooseGraphicsProviderApp.quitLater();
        };
        menu->addMenuElement(
            e172::FactoryMeta::make<GUIButton>(std::string("SDL2"), [apply](auto) { apply(SDL); }));
        menu->addMenuElement(e172::FactoryMeta::make<GUIButton>(std::string("Vulkan"),
                                                                [apply](auto) { apply(Vulkan); }));
        menu->addMenuElement(e172::FactoryMeta::make<GUIButton>(std::string("Console"),
                                                                [apply](auto) { apply(Console); }));

        stack->push(menu.get());
        rootElement->addChildElement(stack.get());

        gprovider->loadFont(std::string(),
                            chooseGraphicsProviderApp.context()->absolutePath(
                                "./assets/fonts/ZCOOL.ttf"));

        chooseGraphicsProviderApp.addEntity(rootElement.get());
        chooseGraphicsProviderApp.exec();
    }
    return result;
}

} // namespace

std::shared_ptr<e172::AbstractGraphicsProvider> chooseGraphicsProvider(
    const e172::GameApplication &app)
{
    const auto renderLayer = chooseRenderLayer(app.arguments());

    if (renderLayer == Vulkan) {
        const auto graphicsProvider = std::make_shared<e172::impl::vulkan::GraphicsProvider>(
            app.arguments());
        if (!graphicsProvider->isValid()) {
            const auto graphicsProvider = std::make_shared<e172::impl::sdl::GraphicsProvider>(
                app.arguments(), "project172", e172::Vector<std::uint32_t>{900, 600});
            if (!graphicsProvider->isValid()) {
                e172::Debug::fatal("error: no graphics provider are valid.");
                std::exit(2);
            }
            return graphicsProvider;
        }
        return graphicsProvider;
    } else if (renderLayer == SDL) {
        return std::make_shared<e172::impl::sdl::GraphicsProvider>(app.arguments(),
                                                                   "project172",
                                                                   e172::Vector<std::uint32_t>{900,
                                                                                               600});
    } else if (renderLayer == Console) {
        return std::make_shared<e172::impl::console::GraphicsProvider>(app.arguments(), std::cout);
    } else {
        return nullptr;
    }
}

// namespace

} // namespace proj172
