#include "registryinfo.h"

#include "objectregistry.h"

RegistryInfo::RegistryInfo(){
}

std::string RegistryInfo::getInfo() {
    return "registry size: " + std::to_string(ObjectRegistry::getInstance()->getSize());
}