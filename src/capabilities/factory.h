#pragma once

#include "warestorage.h"
#include <src/additional/ware/waremultibaycontainer.h>
#include <src/time/elapsedtimer.h>

namespace proj172::core {

class FactoryWareTemplate {
public:
    FactoryWareTemplate(const std::string &ware = std::string(), size_t capacity = 0, size_t amount = 0);
    std::string ware() const;
    size_t capacity() const;
    size_t amount() const;
    friend bool operator==(const FactoryWareTemplate &t0, const FactoryWareTemplate &t1);
    friend bool operator<(const FactoryWareTemplate &t0, const FactoryWareTemplate &t1);

private:
    std::string m_ware;
    size_t m_capacity;
    size_t m_amount;
};

class Factory : public WareStorage {
public:
    Factory(e172::FactoryMeta &&meta);

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::EventHandler *) override;
    virtual void render(e172::AbstractRenderer*) override {};

    // WareStorage interface
protected:
    virtual e172::ptr<AbstractWareContainer> createWareContainer() const override;

private:
    void initializeTemplates();
    void updateContainers();
    void updatePriceTable();

private:
    e172::ElapsedTimer m_timer;
    std::vector<FactoryWareTemplate> m_templates;
};

} // namespace proj172::core
