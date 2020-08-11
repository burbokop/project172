#include "vectorassetexecutor.h"

#include <engine/math/vector.h>
#include <iostream>
VectorAssetExecutor::VectorAssetExecutor()
{

}

e172::Variant VectorAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*, e172::AbstractAudioProvider *) {
    return e172::Variant::fromValue(e172::Vector(
                value.get("x", 0.0).asDouble(),
                value.get("y", 0.0).asDouble()
                ));
}
