#include "nodesassetexecutor.h"

#include <src/additional.h>
#include <src/math/math.h>
#include <src/additional.h>

e172::Variant NodesAssetExecutor::proceed(const e172::Variant &value) {
    std::list<std::pair<e172::Vector<double>, double>> result;
    const auto nodes = value.toList();
    for(const auto& node : nodes) {
        const auto nodeObject = node.toMap();
        const auto offset = nodeObject.at("offset");
        if(offset.isNull()) {
            continue;
        }
        const auto offsetObject = offset.toMap();
        const auto x = offsetObject.at("x");
        if(x.isNull()) {
            continue;
        }
        const auto y = offsetObject.at("y");
        if(y.isNull()) {
            continue;
        }
        const auto angle = nodeObject.at("angle");
        if(angle.isNull()) {
            continue;
        }
        const auto angleValue = e172::Additional::parseRadians(angle.toString());
        if(angleValue.isEmpty()) {
            continue;
        }
        result.push_back({ e172::Vector(x.toDouble(), y.toDouble()), angleValue.value() });
    }
    return e172::Variant::fromValue(result);
}
