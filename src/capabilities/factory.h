#ifndef FACTORY_H
#define FACTORY_H

#include "warestorage.h"

#include <src/additional/ware/waremultibaycontainer.h>

#include <src/engine/time/elapsedtimer.h>

class FactoryWareTemplate {
    std::string m_ware;
    size_t m_capacity;
    size_t m_amount;
public:
    FactoryWareTemplate(const std::string &ware = std::string(), size_t capacity = 0, size_t amount = 0);
    std::string ware() const;
    size_t capacity() const;
    size_t amount() const;
    friend bool operator==(const FactoryWareTemplate &t0, const FactoryWareTemplate &t1);
    friend bool operator<(const FactoryWareTemplate &t0, const FactoryWareTemplate &t1);
};


class Factory : public WareStorage {
    WareMultiBayContainer m_container;
    e172::ElapsedTimer timer;
    std::vector<FactoryWareTemplate> m_templates;
    void initializeTemplates();
public:
    Factory();

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override;

    virtual void render(e172::AbstractRenderer*) override {};
};

#endif // FACTORY_H
