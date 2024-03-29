#include "factory.h"

#include "../additional/ware/waremultibaycontainer.h"
#include <e172/debug.h>
#include <e172/math/math.h>

namespace proj172::core {

void Factory::initializeTemplates() {
    const auto inputTemplates = asset<std::vector<FactoryWareTemplate>>("input");
    const auto outputTemplates = asset<std::vector<FactoryWareTemplate>>("output");
    m_timer = e172::ElapsedTimer(asset<double>("interval"));

    auto container = e172::smart_cast<WareMultiBayContainer>(wareContainer());

    container->setBayCount(inputTemplates.size() + outputTemplates.size());
    m_templates.resize(inputTemplates.size() + outputTemplates.size());
    for(size_t i = 0, count = inputTemplates.size(); i < count; ++i) {
        container->operator[](i).setCapacity(inputTemplates[i].capacity());
        container->operator[](i).setAllowedInput(std::vector<std::string> { inputTemplates[i].ware() });
        m_templates[i] = inputTemplates[i];
    }
    for(size_t i = 0, count = outputTemplates.size(); i < count; ++i) {
        container->operator[](inputTemplates.size() + i).setCapacity(outputTemplates[i].capacity());
        container->operator[](inputTemplates.size() + i).setAllowedOutput(std::vector<std::string> { outputTemplates[i].ware() });

        //FOR DEBUG
        container->operator[](inputTemplates.size() + i)
            .addWare(outputTemplates[i].ware(),
                     outputTemplates[i].capacity() * e172::Random::uniq().nextNormalized<double>(),
                     true);
        //--- -----

        m_templates[inputTemplates.size() + i] = outputTemplates[i];
    }
}

void Factory::updateContainers() {
    auto container = e172::smart_cast<WareMultiBayContainer>(wareContainer());
    for(size_t i = 0; i < container->size(); ++i) {
        const auto templ = m_templates[i];
        const auto ao = container->operator[](i).allowedOutput();

        bool accepted = false;
        if(const auto ao_ptr = std::get_if<std::vector<std::string>>(&ao)) {
            if(ao_ptr->size() > 0) {
                accepted = true;
                if(container->operator[](i).wareAwailableAdditingAmount(templ.ware(), templ.amount(), true) != templ.amount())
                    return;

            }
        }

        if(!accepted) {
            const auto ai = container->operator[](i).allowedInput();
            if(const auto ai_ptr = std::get_if<std::vector<std::string>>(&ai)) {
                if(ai_ptr->size() > 0) {
                    if(container->operator[](i).wareInfoCount() == 0)
                        return;

                    if(container->operator[](i).wareAwailableRemovingAmount(0, templ.amount(), true) != templ.amount())
                        return;
                }
            }
        }
    }

    for(size_t i = 0; i < container->size(); ++i) {
        const auto templ = m_templates[i];
        const auto ao = container->operator[](i).allowedOutput();
        if(const auto ao_ptr = std::get_if<std::vector<std::string>>(&ao)) {
            if(ao_ptr->size() > 0)
                container->operator[](i).addWare(templ.ware(), templ.amount(), true);
        }
        const auto ai = container->operator[](i).allowedInput();
        if(const auto ai_ptr = std::get_if<std::vector<std::string>>(&ai)) {
            if(ai_ptr->size() > 0 && container->operator[](i).wareInfoCount() > 0)
                container->operator[](i).removeWare(0, templ.amount(), true);
        }
    }
}

void Factory::updatePriceTable() {
    const auto& container = e172::smart_cast<WareMultiBayContainer>(wareContainer());
    double wareDefaultPrice = 12;
    double wareDefaultPriceDelta = 8;

    for(size_t i = 0; i < container->size(); ++i) {        
        const auto& subContainer = container->operator[](i);
        const auto& tmpl = m_templates[i];
        const auto& full = subContainer.full();
        if(subContainer.isOutputAllowed(tmpl.ware())) {
            priceTable()->setBuyPrice(tmpl.ware(),
                                      e172::Math::map<double>(full,
                                                              0,
                                                              1,
                                                              wareDefaultPrice
                                                                  - wareDefaultPriceDelta,
                                                              wareDefaultPrice
                                                                  + wareDefaultPriceDelta));
        } else {
            priceTable()->removeBuyPrice(tmpl.ware());
        }
        if(subContainer.isInputAllowed(tmpl.ware())) {
            priceTable()->setSellPrice(tmpl.ware(),
                                       e172::Math::map<double>(full,
                                                               0,
                                                               1,
                                                               wareDefaultPrice
                                                                   + wareDefaultPriceDelta,
                                                               wareDefaultPrice
                                                                   - wareDefaultPriceDelta));
        } else {
            priceTable()->removeSellPrice(tmpl.ware());
        }
    }
}

Factory::Factory(e172::FactoryMeta &&meta)
    : WareStorage(std::move(meta))
{
    registerInitFunction(this, &Factory::initializeTemplates);
}

void Factory::proceed(e172::Context *, e172::EventHandler *) {
    if (m_timer.check()) {
        updateContainers();
        updatePriceTable();
    }
}

size_t FactoryWareTemplate::capacity() const {
    return m_capacity;
}

size_t FactoryWareTemplate::amount() const {
    return m_amount;
}

bool operator<(const FactoryWareTemplate &t0, const FactoryWareTemplate &t1) {
    return t0.m_ware < t1.m_ware && t0.m_amount < t1.m_amount && t0.m_capacity < t1.m_capacity;
}

FactoryWareTemplate::FactoryWareTemplate(const std::string &ware, size_t capacity, size_t amount) {
    m_ware = ware;
    m_capacity = capacity;
    m_amount = amount;
}

std::string FactoryWareTemplate::ware() const {
    return m_ware;
}

bool operator==(const FactoryWareTemplate &t0, const FactoryWareTemplate &t1) {
    return t0.m_ware == t1.m_ware && t0.m_amount == t1.m_amount && t0.m_capacity == t1.m_capacity;
}

e172::ptr<AbstractWareContainer> Factory::createWareContainer() const {
    return new WareMultiBayContainer();
}

} // namespace proj172::core
