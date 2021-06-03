#include "dockingtask.h"
#include "sellwaretask.h"
#include <src/capabilities/controller.h>
#include <src/context.h>
#include <src/units/unit.h>

e172::ptr<WareStorage> SellWareTask::findBuyerStorage(e172::Context *context) {
    int64_t maxPrice = 0;
    e172::ptr<WareStorage> targetStorage;

    for(const auto& e : context->entities()) {
        if(const auto& unit = e172::smart_cast<Unit>(e)) {
            if(const auto& storage = unit->capability<WareStorage>()) {
                if(const auto& controller = unit->capability<Controller>()) {
                    if(controller->person()) {
                        const auto currentSellPrice = storage->priceTable()->price(m_targetWare).sellPrice();
                        if(currentSellPrice.isDefined() && currentSellPrice.value() > maxPrice) {
                            maxPrice = currentSellPrice.value();
                            targetStorage = storage;
                        }
                    }
                }
            }
        }
    }
    return targetStorage;
}

SellWareTask::SellWareTask(const std::string &targetWare) {
    m_targetWare = targetWare;
}

void SellWareTask::proceed(e172::Context *) {}

bool SellWareTask::start(e172::Context *context) {
    if(auto controller = parentController()) {
        if(auto parentUnit = controller->parentUnit()) {
            if(auto storage = parentUnit->capability<WareStorage>()) {
                if(auto person = controller->person()) {
                    const auto wareIndex = storage->indexOf(m_targetWare);
                    if(wareIndex.has_value()) {
                        const auto wareRef = storage->ref(wareIndex.value());
                        if(auto buyerStorage = findBuyerStorage(context)) {
                            executeChildTask(new DockingTask(buyerStorage->parentUnit()), context, [wareRef, buyerStorage, person, this](const auto&){
                                const auto status = person->sellWare(wareRef, buyerStorage);
                                out() << "status: " << status << std::endl;
                                completeTask();
                            });
                            return true;
                        } else {
                            out() << "error: buyer not found" << std::endl;
                        }
                    } else {
                        out() << "error: target ware not found in storage" << std::endl;
                    }
                } else {
                    out() << "error: person missing" << std::endl;
                }
            } else {
                out() << "error: ware storage missing" << std::endl;
            }
        } else {
            out() << "error: parent unit missing" << std::endl;
        }
    } else {
        out() << "error: parent controller missing" << std::endl;
    }
    completeTask();
    return false;
}

void SellWareTask::initFromCommand(const std::vector<std::string> &args, e172::Context *context) {
    if (args.size() > 1) {
        m_targetWare = args[1];
    } else {
        out() << "error: must have 2 arguments" << std::endl;
        completeTask();
    }
}
