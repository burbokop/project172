#ifndef STRINGASSETEXECUTOR_H
#define STRINGASSETEXECUTOR_H

#include "assetexecutor.h"



class StringAssetExecutor : public AssetExecutor {
public:
    StringAssetExecutor();

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *) override;
};

#endif // STRINGASSETEXECUTOR_H
