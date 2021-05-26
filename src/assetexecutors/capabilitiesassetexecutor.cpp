#include "capabilitiesassetexecutor.h"

#include <src/capabilities/capability.h>

CapabilitiesAssetExecutor::CapabilitiesAssetExecutor() {

}

e172::Variant CapabilitiesAssetExecutor::proceed(const e172::Variant &value) {
    std::vector<e172::ptr<Capability>> result;
    const auto list = value.toList();
    result.reserve(list.size());
    for(const auto& l : list) {
        result.push_back(createLoadable<Capability>(l.toMap()));
    }
    return e172::Variant::fromValue(result);
}
