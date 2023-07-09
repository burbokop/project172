#include "animatorassetexecutor.h"

#include <e172/graphics/abstractgraphicsprovider.h>
#include <e172/utility/animator.h>

namespace proj172::core {

e172::Variant AnimatorAssetExecutor::proceed(const e172::Variant &value) {
    const auto object = value.toMap();
    if (object.size() > 0 && graphicsProvider()) {
        const auto spritesheet = object.at("spritesheet");
        const auto frames = object.at("frames");
        const auto tracks = object.at("tracks");
        const auto play = object.at("play");
        if(!spritesheet.isNull()) {
            e172::Animator anim(graphicsProvider()->loadImage(fullPath(spritesheet.toString())), frames.isNull() ? 1 : frames.toInt(), tracks.isNull() ? 1 : tracks.toInt());
            if(!play.isNull()) {
                if(play == "loop") {
                    anim.play(e172::Animator::Loop);
                } else {
                    anim.play(e172::Animator::NotRender);
                }
            } else {
                anim.play(e172::Animator::Loop);
            }
            return e172::Variant::fromValue(anim);
        }
    }
    return e172::Variant();
}

} // namespace proj172::core
