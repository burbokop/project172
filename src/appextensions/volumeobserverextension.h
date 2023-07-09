#pragma once

#include <e172/gameapplication.h>
#include <e172/utility/observer.h>

class VolumeObserverExtension : public e172::GameApplicationExtension {
    e172::Observer<e172::Variant> value;
    size_t connectionId = 0;
public:
    VolumeObserverExtension();
    ~VolumeObserverExtension();

    // GameApplicationExtension interface
public:
    virtual void proceed(e172::GameApplication *application) override;
};

