#include "stringassetexecutor.h"

StringAssetExecutor::StringAssetExecutor()
{

}


e172::Variant StringAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) {
    return e172::Variant::fromValue(value.asString());
}
