#include "vectorassetexecutor.h"

#include <engine/math/vector.h>

VectorAssetExecutor::VectorAssetExecutor()
{

}

e172::Variant VectorAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*) {
    return e172::Variant::fromValue(e172::Vector(
                value.get("x", 0.0).asDouble(),
                value.get("y", 0.0).asDouble()
                ));
}
