#pragma once

#include <e172/gameapplication.h>

namespace proj172::core {

class ScreenSettingsExtension : public e172::GameApplicationExtension {
public:
    ScreenSettingsExtension();

    // GameApplicationExtension interface
public:
    virtual void proceed(e172::GameApplication *application) override;
};

} // namespace proj172::core
