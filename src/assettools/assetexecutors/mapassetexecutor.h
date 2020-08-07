#ifndef MAPASSETEXECUTOR_H
#define MAPASSETEXECUTOR_H

#include "assetexecutor.h"



class MapAssetExecutor : public AssetExecutor {
public:
    MapAssetExecutor();

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *) override;
};

#endif // MAPASSETEXECUTOR_H
