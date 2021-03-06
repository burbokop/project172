#ifndef RECIEPTASSETEXECUTOR_H
#define RECIEPTASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>



class RecieptAssetExecutor : public e172::AbstractAssetExecutor {
public:
    RecieptAssetExecutor();

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) override;
};

#endif // RECIEPTASSETEXECUTOR_H
