#include "nodesassetexecutor.h"

#include <src/additional.h>

#include <src/math/math.h>


NodesAssetExecutor::NodesAssetExecutor() {}

std::optional<double> NodesAssetExecutor::parseAngle(const std::string &str) {
    const auto angleParts = e172::Additional::split(str, '/');
    if(angleParts.size() > 1) {
        if(angleParts[0] == "Pi") {
            const auto divider = std::stod(angleParts[1]);
            if(divider != e172::Math::null) {
                return e172::Math::Pi / divider;
            }
        } else if(angleParts[0] == "-Pi") {
            const auto divider = std::stod(angleParts[1]);
            if(divider != e172::Math::null) {
                return -e172::Math::Pi / divider;
            }
        }
    } else if(angleParts.size() > 1) {
        return std::stod(angleParts[1]);
    }
    if(str == "Pi") {
        return e172::Math::Pi;
    } else if(str == "-Pi") {
        return -e172::Math::Pi;
    }
    return std::nullopt;
}


e172::Variant NodesAssetExecutor::proceed(const e172::Variant &value) {
    std::list<std::pair<e172::Vector, double>> result;
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
        const auto angleValue = parseAngle(angle.toString());
        if(!angleValue.has_value()) {
            continue;
        }
        result.push_back({ e172::Vector(x.toDouble(), y.toDouble()), angleValue.value() });
    }
    return e172::Variant::fromValue(result);
}
