#include "screensettingsextension.h"

#include "../messagetype.h"
#include <e172/context.h>
#include <e172/graphics/abstractgraphicsprovider.h>

namespace proj172::core {

ScreenSettingsExtension::ScreenSettingsExtension()
    : e172::GameApplicationExtension(PostProceedExtension)
{}

void ScreenSettingsExtension::proceed(e172::GameApplication *application) {
    if (const auto context = application->context()) {
        if (const auto renderer = application->renderer()) {
            context->popMessage(~MessageType::ChangeResolution,
                                [renderer](auto, const e172::Variant &value) {
                                    renderer->setResolution(
                                        value.toMathVector<double>().into<std::uint32_t>());
                                });

            context->popMessage(~MessageType::ChangeFullscreen,
                                [renderer](auto, const e172::Variant &value) {
                                    renderer->setFullscreen(value.toBool());
                                });
        }
    }
}

} // namespace proj172::core
