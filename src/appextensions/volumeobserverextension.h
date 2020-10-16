#ifndef VOLUMEOBSERVEREXTENSION_H
#define VOLUMEOBSERVEREXTENSION_H

#include <src/gameapplication.h>

#include <src/utility/observer.h>

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

#endif // VOLUMEOBSERVEREXTENSION_H
