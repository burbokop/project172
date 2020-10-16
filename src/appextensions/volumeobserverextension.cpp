#include "volumeobserverextension.h"

#include <src/context.h>
#include <src/audio/abstractaudioprovider.h>

VolumeObserverExtension::VolumeObserverExtension()
    : e172::GameApplicationExtension(GameApplicationExtension::InitExtension) {}

VolumeObserverExtension::~VolumeObserverExtension() {
    value.disconnect(connectionId);
}

void VolumeObserverExtension::proceed(e172::GameApplication *application) {
    value = application->context()->settingValue("general_volume");
    connectionId = value.connect([application](const e172::Variant &v) {
        if(application && application->audioProvider())
            application->audioProvider()->setGeneralVolume(v.toDouble());
    });
}
