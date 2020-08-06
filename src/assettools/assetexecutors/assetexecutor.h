#ifndef ASSETEXECUTOR_H
#define ASSETEXECUTOR_H

#include <engine/variant.h>

#include <json/json.h>

class AssetExecutor {
public:
    AssetExecutor();
    virtual ~AssetExecutor();
    virtual e172::Variant proceed(const Json::Value &value) = 0;
};

#endif // ASSETEXECUTOR_H
