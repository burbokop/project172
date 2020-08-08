#include "audioassetexecutor.h"

#include <audio/audioplayer.h>

AudioAssetExecutor::AudioAssetExecutor() {}

e172::Variant AudioAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*) {
    if(value.isObject()) {
        Json::Value audioStart = value["start"];
        Json::Value audioLoop = value["loop"];
        Json::Value audioStop = value["stop"];
        const auto volume = value.get("volume", 1).asDouble();

        if(audioStart.isString()) {
            if(audioLoop.isString() && audioStop.isString()) {
                AudioPlayer p(
                            Mix_LoadWAV(fullPath(audioStart.asString()).c_str()),
                            Mix_LoadWAV(fullPath(audioLoop.asString()).c_str()),
                            Mix_LoadWAV(fullPath(audioStop.asString()).c_str())
                            );
                p.setVolume(volume);
                return e172::Variant::fromValue(p);
            } else {
                AudioPlayer p(
                            Mix_LoadWAV(fullPath(audioStart.asString()).c_str())
                            );
                p.setVolume(volume);
                return e172::Variant::fromValue(p);
            }
        }
    } else if (value.isString()) {
        return e172::Variant::fromValue(AudioPlayer(
                                            Mix_LoadWAV(fullPath(value.asString()).c_str())
                                            ));
    }
    return e172::Variant();
}
