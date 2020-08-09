#include "numberassetexecutor.h"

#include <iostream>

NumberAssetExecutor::NumberAssetExecutor()
{

}

e172::Variant NumberAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*, e172::AbstractAudioProvider *) {
    return e172::Variant::fromValue(value.asDouble());
}
