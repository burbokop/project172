#include "buywaretask.h"
#include "dockingtask.h"
#include <src/capabilities/controller.h>
#include <src/context.h>

BuyWareTask::BuyWareTask(const std::string &ware) {
    m_targetWare = ware;
}

void BuyWareTask::proceed(e172::Context *context) {
}

bool BuyWareTask::start(e172::Context *context) {
    if(const auto unit = parentController()->parentUnit()) {
        unit->position();
    }

    //TO DO use `context->autoIteratingEntity();`

    int64_t minPrice = std::numeric_limits<int64_t>::max();
    e172::ptr<Unit> targetUnit = nullptr;
    for(const auto& e : context->entities()) {
        if(const auto& unit = e172::smart_cast<Unit>(e)) {
            if(const auto& storage = unit->capability<WareStorage>()) {
                const auto index = storage->indexOf(m_targetWare);
                if(index.has_value()) {
                    const auto price = storage->priceTable()->price(index.value());
                    if(price.buyPrice().has_value()) {
                        const auto buyPrice = price.buyPrice().value();
                        if(buyPrice < minPrice) {
                            minPrice = buyPrice;
                            targetUnit = unit;
                        }
                    }
                }
            }
        }
    }
    if(targetUnit) {
        return executeChildTask(new DockingTask(targetUnit), context);
    } else {
        return false;
    }
}