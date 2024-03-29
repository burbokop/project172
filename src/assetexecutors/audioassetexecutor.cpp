#include "audioassetexecutor.h"

#include <e172/additional.h>
#include <e172/audio/abstractaudioprovider.h>
#include <e172/audio/audioplayer.h>

namespace proj172::core {

e172::Variant AudioAssetExecutor::proceed(const e172::Variant &value) {
    if (audioProvider()) {
        if (value.isString()) {
            return e172::Variant::fromValue(
                e172::AudioPlayer(audioProvider()->reserveChannel(),
                                  audioProvider()->loadAudioSample(
                                      fullPath(value.toString()).c_str())));
        } else {
            const auto object = value.toMap();
            if (object.size() > 0) {
                const auto audioStart = e172::Additional::value(object, "start");
                const auto audioLoop = e172::Additional::value(object, "loop");
                const auto audioStop = e172::Additional::value(object, "stop");
                const auto volume = e172::Additional::value(object, "volume", 1).toDouble();

                if (audioStart.isString()) {
                    if (audioLoop.isString() && audioStop.isString()) {
                        e172::AudioPlayer
                            p(audioProvider()->reserveChannel(),
                              audioProvider()->loadAudioSample(fullPath(audioStart.toString())),
                              audioProvider()->loadAudioSample(fullPath(audioLoop.toString())),
                              audioProvider()->loadAudioSample(fullPath(audioStop.toString())));

                        p.setVolume(volume);
                        return e172::Variant::fromValue(p);
                    } else {
                        e172::AudioPlayer p(audioProvider()->reserveChannel(),
                                            audioProvider()->loadAudioSample(
                                                fullPath(audioStart.toString())));
                        p.setVolume(volume);
                        return e172::Variant::fromValue(p);
                    }
                }
            }
        }
    }
    return e172::Variant();
}

} // namespace proj172::core
