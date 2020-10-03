#include "spriteassetexecutor.h"

#include <src/engine/graphics/abstractgraphicsprovider.h>

#include <src/animator.h>

SpriteAssetExecutor::SpriteAssetExecutor() {}

e172::Variant SpriteAssetExecutor::proceed(const e172::Variant &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *) {
    if(value.isString()) {
        const auto path = fullPath(value.toString());
        auto anim = Animator(graphicsProvider->loadImage(path));
        anim.play(Animator::Loop);
        return e172::Variant::fromValue(anim);
    }
    return e172::Variant();
}
