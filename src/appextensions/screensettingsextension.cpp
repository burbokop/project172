#include "screensettingsextension.h"

#include "../messagetype.h"
#include <src/context.h>
#include <src/graphics/abstractgraphicsprovider.h>

namespace proj172::core {

ScreenSettingsExtension::ScreenSettingsExtension()
    : e172::GameApplicationExtension(PostProceedExtension)
{}

void ScreenSettingsExtension::proceed(e172::GameApplication *application) {
    auto context = application->context();
    const auto graphicsProcider = application->graphicsProvider();
    if(context && graphicsProcider) {
        auto renderer = graphicsProcider->renderer();
        if (renderer) {
            context->popMessage(~MessageType::ChangeResolution,
                                [renderer](auto, const e172::Variant &value) {
                                    renderer->setResolution(value.toMathVector<double>());
                                });

            context->popMessage(~MessageType::ChangeFullscreen,
                                [renderer](auto, const e172::Variant &value) {
                                    renderer->setFullscreen(value.toBool());
                                });
        }
    }
}

} // namespace proj172::core
