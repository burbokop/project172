#include "buywaretask.h"
#include "dockingtask.h"
#include <src/capabilities/controller.h>
#include <src/context.h>
#include <src/debug.h>
#include <src/consolecolor.h>


BuyWareTask::BuyWareTask(const e172::Option<std::string> &ware) {
    m_targetWare = ware;
}

void BuyWareTask::dockingCompleated(const WareStorage::WareRef &wareRef) {
    if(const auto& controller = parentController()) {
        if(const auto& unit = controller->parentUnit()) {
            if(const auto& storage = unit->capability<WareStorage>()) {
                const auto status = controller->person()->buyWare(wareRef, storage);
                out() << status << std::endl;
            } else {
                out() << "unit not have storage" << std::endl;
            }
        } else {
            out() << "controller do not have parent unit" << std::endl;
        }
    } else {
        out() << "parent controller is null" << std::endl;
    }
    if(m_targetWare.isDefined()) {
        completeTask(m_targetWare.value());
    } else {
        completeTask();
    }
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
                        out() << "ware choosed: " << w << std::endl;
                    });
                }

                if(m_targetWare.isDefined()) {
                    const auto index = storage->indexOf(m_targetWare.value());
                    if(index.has_value()) {
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
        out() << "error: not found candidate for target unit" << std::endl;
        completeTask();
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
        out() << "error: missing argument." << std::endl << "using: BuyWareTask>unit [ware name|?=any]" << std::endl;
        completeTask();
    }
}
