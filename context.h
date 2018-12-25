#ifndef CONTEXT_H
#define CONTEXT_H

#include "worker.h"
#include "assetmanager.h"

class Context : public Object
{
private:
    std::vector<Worker *> *units;
    AssetManager *assets;
public:
    Context(std::vector<Worker*> *units = nullptr, AssetManager *assets = nullptr);

    std::vector<Worker *> *getUnits() const;
    AssetManager *getAssets() const;
};

#endif // CONTEXT_H
