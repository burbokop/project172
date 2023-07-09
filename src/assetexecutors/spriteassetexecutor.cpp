#include "spriteassetexecutor.h"

#include <e172/graphics/abstractgraphicsprovider.h>
#include <e172/utility/animator.h>

namespace proj172::core {

e172::Variant SpriteAssetExecutor::proceed(const e172::Variant &value) {
    if (value.isString() && graphicsProvider()) {
        const auto path = fullPath(value.toString());
        auto anim = e172::Animator(graphicsProvider()->loadImage(path));
        anim.play(e172::Animator::Loop);
        return e172::Variant::fromValue(anim);
    }
    return e172::Variant();
}

} // namespace proj172::core
