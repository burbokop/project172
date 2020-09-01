#include "audioassetexecutor.h"

#include <src/audio/audioplayer.h>

#include <src/engine/audio/abstractaudioprovider.h>

AudioAssetExecutor::AudioAssetExecutor() {}
#include <iostream>
e172::Variant AudioAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*, e172::AbstractAudioProvider *audioProvider) {
    if(value.isObject()) {
        Json::Value audioStart = value["start"];
        Json::Value audioLoop = value["loop"];
        Json::Value audioStop = value["stop"];
        const auto volume = value.get("volume", 1).asDouble();

        if(audioStart.isString()) {
            if(audioLoop.isString() && audioStop.isString()) {
                AudioPlayer p(
                            audioProvider->reserveChannel(),
                            audioProvider->loadAudioSample(fullPath(audioStart.asString()).c_str()),
                            audioProvider->loadAudioSample(fullPath(audioLoop.asString()).c_str()),
                            audioProvider->loadAudioSample(fullPath(audioStop.asString()).c_str())
                            );

                p.setVolume(volume);
                return e172::Variant::fromValue(p);
            } else {
                AudioPlayer p(
                            audioProvider->reserveChannel(),
                            audioProvider->loadAudioSample(fullPath(audioStart.asString()).c_str())
                            );
                p.setVolume(volume);
                return e172::Variant::fromValue(p);
            }
        }
    } else if (value.isString()) {
        return e172::Variant::fromValue(AudioPlayer(
                                            audioProvider->reserveChannel(),
                                            audioProvider->loadAudioSample(fullPath(value.asString()).c_str())
                                            ));
    }
    return e172::Variant();
}
