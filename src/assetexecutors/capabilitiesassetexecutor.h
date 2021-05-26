#ifndef CAPABILITIESASSETEXECUTOR_H
#define CAPABILITIESASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>



class CapabilitiesAssetExecutor : public e172::AbstractAssetExecutor {
public:
    CapabilitiesAssetExecutor();

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

#endif // CAPABILITIESASSETEXECUTOR_H
