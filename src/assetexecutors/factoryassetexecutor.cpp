#include "factoryassetexecutor.h"

#include "../capabilities/factory.h"

namespace proj172::core {

RecieptAssetExecutor::RecieptAssetExecutor() {}

e172::Variant RecieptAssetExecutor::proceed(const e172::Variant &value) {
    const auto list = value.toList();
    std::vector<FactoryWareTemplate> result;
    for(auto v : list) {
        const auto object = v.toMap();
        result.push_back(FactoryWareTemplate (object.at("ware").toString(), object.at("capacity").toUInt(), object.at("amount").toUInt()));
    }
    return e172::Variant::fromValue(result);
}

} // namespace proj172::core
