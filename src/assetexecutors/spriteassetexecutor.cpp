#include "spriteassetexecutor.h"

#include <src/graphics/abstractgraphicsprovider.h>

#include <src/utility/animator.h>

SpriteAssetExecutor::SpriteAssetExecutor() {}

e172::Variant SpriteAssetExecutor::proceed(const e172::Variant &value) {
    if(value.isString()) {
        const auto path = fullPath(value.toString());
        auto anim = e172::Animator(graphicsProvider()->loadImage(path));
        anim.play(e172::Animator::Loop);
        return e172::Variant::fromValue(anim);
    }
    return e172::Variant();
}
