#include "loadable.h"



std::string Loadable::className() const {
    return m_className;
}

std::string Loadable::loadableId() const
{
    return m_loadableId;
}

AssetProvider *Loadable::assetProvider() const {
    return m_assetProvider;
}

void Loadable::registerInitFunction(const std::function<void ()> &function) {
    if(released) {

    } else {
        initialize_functions.push_back(function);
    }
}

Loadable::Loadable() {}

Loadable::~Loadable() {}
