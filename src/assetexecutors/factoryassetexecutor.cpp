#include "factoryassetexecutor.h"

#include <src/capabilities/factory.h>

RecieptAssetExecutor::RecieptAssetExecutor()
{

}

e172::Variant RecieptAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *audioProvider) {
    std::vector<FactoryWareTemplate> result;
    for(auto v : value) {
        result.push_back(FactoryWareTemplate (v["ware"].asString(), v["capacity"].asUInt(), v["amount"].asUInt()));
    }
    return e172::Variant::fromValue(result);
}
