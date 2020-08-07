#include "spriteassetexecutor.h"

#include <engine/graphics/abstractgraphicsprovider.h>

#include <animator.h>

SpriteAssetExecutor::SpriteAssetExecutor() {}

e172::Variant SpriteAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider) {
    auto anim = Animator(graphicsProvider->loadImage(fullPath(value.asString())));
    anim.play(Animator::LOOP);
    return e172::Variant::fromValue(anim);
}
