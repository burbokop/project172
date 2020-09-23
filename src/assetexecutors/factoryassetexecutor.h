#ifndef RECIEPTASSETEXECUTOR_H
#define RECIEPTASSETEXECUTOR_H

#include <src/engine/assettools/abstractassetexecutor.h>



class RecieptAssetExecutor : public e172::AbstractAssetExecutor
{
public:
    RecieptAssetExecutor();

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *audioProvider) override;
};

#endif // RECIEPTASSETEXECUTOR_H
