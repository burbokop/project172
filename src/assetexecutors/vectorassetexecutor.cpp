#include "vectorassetexecutor.h"

#include <src/engine/math/vector.h>

VectorAssetExecutor::VectorAssetExecutor() {}

e172::Variant VectorAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*, e172::AbstractAudioProvider *) {
    return e172::Variant::fromValue(e172::Vector(
                value.get("x", 0.0).asDouble(),
                value.get("y", 0.0).asDouble()
                ));
}
