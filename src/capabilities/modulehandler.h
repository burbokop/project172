#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <iterator>
#include <algorithm>
#include "modules/module.h"

namespace proj172::core {

class ModuleHandler : public Capability {
    std::vector<e172::ptr<Module>> m_modules;
protected:

    bool setParentUnit(const e172::ptr<Unit> &parent) override;
public:
    ModuleHandler(e172::FactoryMeta &&meta);

    void addModule(const e172::ptr<Module> &module);
    void removeModule(const e172::ptr<Module> &module);

    std::vector<e172::ptr<Module>> modules() { return m_modules; }

    template<typename T>
    std::vector<e172::ptr<T>> modules()
    {
        std::vector<e172::ptr<T>> result;
        for (const auto &module : m_modules) {
            if (const auto &casted = e172::smart_cast<T>(module)) {
                result.push_back(casted);
            }
        }
        return result;
    }

    template<typename T>
    bool hasModuleOf() const
    {
        const auto name = e172::Type<T>::name();
        for (const auto &module : m_modules) {
            if (e172::smart_cast<T>(module)) {
                return true;
            }
        }
        return false;
    }

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core

#endif // MODULEHANDLER_H
