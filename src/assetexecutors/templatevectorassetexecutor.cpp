#include "templatevectorassetexecutor.h"

TemplateVectorAssetExecutor::TemplateVectorAssetExecutor() {}

e172::Variant TemplateVectorAssetExecutor::proceed(const e172::Variant &value) {
    std::vector<e172::LoadableTemplate> result;
    const auto list = value.toList();
    result.reserve(list.size());
    for(const auto& l : list) {
        if(l.isString()) {
            result.push_back(loadTemplate(l.toString()));
        } else {
            result.push_back(createTemplate(l.toMap()));
        }
    }
    return e172::Variant::fromValue(result);
}
