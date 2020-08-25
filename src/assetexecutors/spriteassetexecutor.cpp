#include "spriteassetexecutor.h"

#include <src/engine/graphics/abstractgraphicsprovider.h>

#include <src/animator.h>
#include <iostream>

SpriteAssetExecutor::SpriteAssetExecutor() {}

e172::Variant SpriteAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *) {
    const auto path = fullPath(value.asString());
    auto anim = Animator(graphicsProvider->loadImage(path));
    anim.play(Animator::Loop);
    return e172::Variant::fromValue(anim);
}
