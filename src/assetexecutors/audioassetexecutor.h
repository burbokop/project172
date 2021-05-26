#ifndef AUDIOASSETEXECUTOR_H
#define AUDIOASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>



class AudioAssetExecutor : public e172::AbstractAssetExecutor {
public:
    AudioAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const e172::Variant &value) override;
};

#endif // AUDIOASSETEXECUTOR_H
