#include "vectorassetexecutor.h"

#include <src/math/vector.h>

VectorAssetExecutor::VectorAssetExecutor() {}

e172::Variant VectorAssetExecutor::proceed(const e172::Variant &value) {
    const auto object = value.toMap();
    return e172::Variant::fromValue(e172::Vector(
                object.at("x").toDouble(),
                object.at("y").toDouble()
                ));
}
