#include "audioassetexecutor.h"

#include <src/audio/audioplayer.h>

#include <src/engine/audio/abstractaudioprovider.h>

#include <src/engine/additional.h>

AudioAssetExecutor::AudioAssetExecutor() {}

e172::Variant AudioAssetExecutor::proceed(const e172::Variant &value, e172::AbstractGraphicsProvider*, e172::AbstractAudioProvider *audioProvider) {
    if (value.isString()) {
        return e172::Variant::fromValue(AudioPlayer(
                                            audioProvider->reserveChannel(),
                                            audioProvider->loadAudioSample(fullPath(value.toString()).c_str())
                                            ));
    } else {
        const auto object = value.toMap();
        if(object.size() > 0) {
            const auto audioStart = e172::Additional::value(object, "start");
            const auto audioLoop = e172::Additional::value(object, "loop");
            const auto audioStop = e172::Additional::value(object, "stop");
            const auto volume = e172::Additional::value(object, "volume", 1).toDouble();

            if(audioStart.isString()) {
                if(audioLoop.isString() && audioStop.isString()) {
                    AudioPlayer p(
                                audioProvider->reserveChannel(),
                                audioProvider->loadAudioSample(fullPath(audioStart.toString())),
                                audioProvider->loadAudioSample(fullPath(audioLoop.toString())),
                                audioProvider->loadAudioSample(fullPath(audioStop.toString()))
                                );

                    p.setVolume(volume);
                    return e172::Variant::fromValue(p);
                } else {
                    AudioPlayer p(
                                audioProvider->reserveChannel(),
                                audioProvider->loadAudioSample(fullPath(audioStart.toString()))
                                );
                    p.setVolume(volume);
                    return e172::Variant::fromValue(p);
                }
            }
        }
    }
    return e172::Variant();
}
