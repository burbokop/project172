#include "numberassetexecutor.h"

#include <iostream>

NumberAssetExecutor::NumberAssetExecutor()
{

}

e172::Variant NumberAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*) {
    return e172::Variant::fromValue(value.asDouble());
}
