#ifndef STRINGASSETEXECUTOR_H
#define STRINGASSETEXECUTOR_H

#include <src/engine/assettools/abstractassetexecutor.h>



class StringAssetExecutor : public e172::AbstractAssetExecutor {
public:
    StringAssetExecutor();

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) override;
};

#endif // STRINGASSETEXECUTOR_H
