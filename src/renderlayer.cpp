#include "renderlayer.h"

#include "background.h"
#include "gui/base/guicontainer.h"
#include "gui/base/guimenu.h"
#include "gui/base/guistack.h"
#include "gui/guibutton.h"
#include <e172/context.h>
#include <e172/debug.h>
#include <e172/gameapplication.h>
#include <e172/impl/console/eventprovider.h>
#include <e172/impl/console/graphicsprovider.h>
#include <e172/impl/sdl/audioprovider.h>
#include <e172/impl/sdl/eventprovider.h>
#include <e172/impl/sdl/graphicsprovider.h>
#include <e172/impl/vulkan/graphicsprovider.h>
#include <fstream>
#include <iostream>

namespace proj172 {

namespace {

enum RenderLayer { Undefined, SDL, Vulkan, Console };

RenderLayer choosePlatformType(const std::vector<std::string> &args)
{
    using namespace proj172::core;
    RenderLayer result = Undefined;
    {
        e172::GameApplication chooseGraphicsProviderApp(args);
        const auto gprovider = std::make_shared<e172::impl::sdl::GraphicsProvider>();
        const auto eventProvider = std::make_shared<e172::impl::sdl::EventProvider>();
        chooseGraphicsProviderApp.setGraphicsProvider(gprovider);
        chooseGraphicsProviderApp.setEventProvider(eventProvider);

        chooseGraphicsProviderApp.initRenderer("choose gprovider",
                                               e172::Vector<std::uint32_t>{118, 168});

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

std::ofstream log("/tmp/event-provider.log");

} // namespace

Platform choosePlatform(const e172::GameApplication &app)
{
    const auto renderLayer = choosePlatformType(app.arguments());

    if (renderLayer == Vulkan) {
        return Platform{.graphicsProvider = std::make_shared<e172::impl::vulkan::GraphicsProvider>(),
                        .eventProvider = std::make_shared<e172::impl::sdl::EventProvider>(),
                        .audioProvider = std::make_shared<e172::impl::sdl::AudioProvider>()};
    } else if (renderLayer == SDL) {
        return Platform{.graphicsProvider = std::make_shared<e172::impl::sdl::GraphicsProvider>(),
                        .eventProvider = std::make_shared<e172::impl::sdl::EventProvider>(),
                        .audioProvider = std::make_shared<e172::impl::sdl::AudioProvider>()};
    } else if (renderLayer == Console) {
        return Platform{.graphicsProvider = std::make_shared<e172::impl::console::GraphicsProvider>(
                            std::cout,
                            e172::impl::console::Style{
                                .colorizer
                                = std::make_shared<e172::impl::console::AnsiTrueColorizer>(1)}),
                        .eventProvider = std::make_shared<e172::impl::console::EventProvider>(log),
                        .audioProvider = nullptr};
    } else {
        throw std::logic_error("no platform choosed");
    }
}

// namespace

} // namespace proj172
