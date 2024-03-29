#include "buywaretask.h"

#include "../capabilities/controller.h"
#include "../units/unit.h"
#include "dockingtask.h"
#include <e172/consolecolor.h>
#include <e172/context.h>
#include <e172/debug.h>

namespace proj172::core {

BuyWareTask::BuyWareTask(const e172::Option<std::string> &ware) {
    m_targetWare = ware;
}

void BuyWareTask::dockingCompleated(const WareStorage::WareRef &wareRef) {
    bool ok = false;
    if(const auto& controller = parentController()) {
        if(const auto& unit = controller->parentUnit()) {
            if(const auto& storage = unit->capability<WareStorage>()) {
                const auto status = controller->person()->buyWare(wareRef, storage);
                out() << status << std::endl;
                if(status == Person::BuyingSuccess) {
                    ok = true;
                }
            } else {
                out() << "BuyWareTask: unit not have storage" << std::endl;
            }
        } else {
            out() << "BuyWareTask: controller do not have parent unit" << std::endl;
        }
    } else {
        out() << "BuyWareTask: parent controller is null" << std::endl;
    }
    completeTask(Result(m_targetWare, ok).toVariant());
}

void BuyWareTask::proceed(e172::Context *) {}

bool BuyWareTask::start(e172::Context *context) {
    if(const auto unit = parentController()->parentUnit()) {
        unit->position();
    }

    //TO DO use `context->autoIteratingEntity();`

    int64_t minPrice = std::numeric_limits<int64_t>::max();
    e172::ptr<Unit> targetUnit;
    WareStorage::WareRef targetWareRef;
    for(const auto& e : context->entities()) {
        if(const auto& unit = e172::smart_cast<Unit>(e)) {
            if(const auto& storage = unit->capability<WareStorage>()) {
                if(m_targetWare.isEmpty()) {
                    storage->priceTable()->findWithBuyPrice().fold([this](const auto& w){
                        m_targetWare = w;
                        out() << "BuyWareTask: ware choosed: " << w << std::endl;
                    });
                }

                if(m_targetWare.isDefined()) {
                    const auto index = storage->indexOf(m_targetWare.value());
                    if(index.isDefined()) {
                        if(storage->wareInfo(index.value()).count() > 0) {
                            const auto price = storage->priceTable()->price(m_targetWare.value());
                            if(price.buyPrice().isDefined()) {
                                const auto buyPrice = price.buyPrice().value();
                                if(buyPrice < minPrice) {
                                    minPrice = buyPrice;
                                    targetUnit = unit;
                                    targetWareRef = WareStorage::WareRef(storage, index.value());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(targetUnit) {
        return executeChildTask(new DockingTask(targetUnit), context, [this, targetWareRef](const auto&){
            dockingCompleated(targetWareRef);
        });
    } else {
        out() << "BuyWareTask: error: not found candidate for target unit" << std::endl;
        completeTask(Result(m_targetWare, false).toVariant());
        return false;
    }
}

void BuyWareTask::initFromCommand(const std::vector<std::string> &args, e172::Context *) {
    if (args.size() > 1) {
        if(args[1] == "?") {
            m_targetWare = e172::None;
        } else {
            m_targetWare = args[1];
        }
    } else {
        out() << "BuyWareTask: error: missing argument." << std::endl << "using: BuyWareTask>unit [ware name|?=any]" << std::endl;
        completeTask(Result(m_targetWare, false).toVariant());
    }
}

bool BuyWareTask::Result::ok() const {
    return m_ok;
}

e172::Option<std::string> BuyWareTask::Result::targetWare() const {
    return m_targetWare;
}

e172::Variant BuyWareTask::Result::toVariant() const {
    return e172::Variant::fromValue(*this);
}

BuyWareTask::Result::Result(e172::Option<std::string> targetWare, bool ok) {
    m_targetWare = targetWare;
    m_ok = ok;
}

} // namespace proj172::core
