#ifndef SCREENSETTINGSEXTENSION_H
#define SCREENSETTINGSEXTENSION_H

#include <src/gameapplication.h>



class ScreenSettingsExtension : public e172::GameApplicationExtension {
public:
    ScreenSettingsExtension();

    // GameApplicationExtension interface
public:
    virtual void proceed(e172::GameApplication *application) override;
};

#endif // SCREENSETTINGSEXTENSION_H
