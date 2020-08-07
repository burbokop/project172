#include "spriteassetexecutor.h"

#include <engine/graphics/abstractgraphicsprovider.h>

#include <animator.h>
#include <iostream>

SpriteAssetExecutor::SpriteAssetExecutor() {}

e172::Variant SpriteAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider) {
    const auto path = fullPath(value.asString());
    auto anim = Animator(graphicsProvider->loadImage(path));
    anim.play(Animator::LOOP);
    return e172::Variant::fromValue(anim);
}
