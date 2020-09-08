#include "registryinfo.h"

#include <src/engine/objectregistry.h>

RegistryInfo::RegistryInfo(){
}

std::string RegistryInfo::getInfo() {
    return "registry size: " + std::to_string(e172::ObjectRegistry::size());
}
