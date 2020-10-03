#include "animatorassetexecutor.h"

#include <src/engine/graphics/abstractgraphicsprovider.h>

#include <src/animator.h>



AnimatorAssetExecutor::AnimatorAssetExecutor() {}

e172::Variant AnimatorAssetExecutor::proceed(const e172::Variant &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *) {
    const auto object = value.toMap();
    if(object.size() > 0) {
        const auto spritesheet = object.at("spritesheet");
        const auto frames = object.at("frames");
        const auto tracks = object.at("tracks");
        const auto play = object.at("play");
        if(!spritesheet.isNull()) {
            Animator anim(graphicsProvider->loadImage(fullPath(spritesheet.toString())), frames.isNull() ? 1 : frames.toInt(), tracks.isNull() ? 1 : tracks.toInt());
            if(!play.isNull()) {
                if(play == "loop") {
                    anim.play(Animator::Loop);
                } else {
                    anim.play(Animator::NotRender);
                }
            } else {
                anim.play(Animator::Loop);
            }
            return e172::Variant::fromValue(anim);
        }
    }
    return e172::Variant();
}
