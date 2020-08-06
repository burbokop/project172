#ifndef ASSETEXECUTOR_H
#define ASSETEXECUTOR_H

#include <engine/variant.h>



class AssetExecutor {
public:
    AssetExecutor();
    virtual e172::Variant proceed() = 0;
};

#endif // ASSETEXECUTOR_H
