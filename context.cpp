#include "context.h"





Context::Context(std::vector<Worker *> *units, AssetManager *assets) {
    this->units = units;
    this->assets = assets;
}

std::vector<Worker *> *Context::getUnits() const {
    return units;
}

AssetManager *Context::getAssets() const {
    return assets;
}
