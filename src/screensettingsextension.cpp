#include "screensettingsextension.h"

#include <src/engine/context.h>
#include <src/engine/graphics/abstractgraphicsprovider.h>

ScreenSettingsExtension::ScreenSettingsExtension()
    : e172::GameApplicationExtension(PreRenderExtension) {}

void ScreenSettingsExtension::proceed(e172::GameApplication *application) {
    auto context = application->context();
    const auto graphicsProcider = application->graphicsProvider();
    if(context && graphicsProcider) {
        auto renderer = graphicsProcider->renderer();
        if(renderer) {
            context->popMessage(e172::Context::CHANGE_RESOLUTION,
                                [renderer](auto, const e172::Variant& value) {
                renderer->setResolution(value.toMathVector());
            });
            context->popMessage(e172::Context::CHANGE_FULLSCREEN,
                                [renderer](auto, const e172::Variant& value) {
                renderer->setFullscreen(value.toBool());
            });
        }
    }
}


