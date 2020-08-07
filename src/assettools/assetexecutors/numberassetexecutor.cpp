#include "numberassetexecutor.h"

NumberAssetExecutor::NumberAssetExecutor()
{

}

e172::Variant NumberAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider*) {
    return e172::Variant::fromValue(value.asDouble());
}
