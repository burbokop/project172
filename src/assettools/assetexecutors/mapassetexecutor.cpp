#include "mapassetexecutor.h"

MapAssetExecutor::MapAssetExecutor() {

}


e172::Variant MapAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *) {
    e172::VariantMap map;
    for(auto it = value.begin(); it != value.end(); it++) {
        std::string key = it.key().asString();
        std::string value = it->asString();
        map[key] = value;
    }
    return map;
}
