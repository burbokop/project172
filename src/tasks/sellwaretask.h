#ifndef SELLWARETASK_H
#define SELLWARETASK_H

#include "task.h"

namespace proj172::core {

class WareStorage;
class Person;

class SellWareTask : public Task {
    std::string m_targetWare;

    e172::ptr<WareStorage> findBuyerStorage(e172::Context *context);
public:
    SellWareTask(const std::string& targetWare = std::string());

    // Task interface
public:
    virtual void proceed(e172::Context *) override;
    virtual bool start(e172::Context *context) override;
    virtual void initFromCommand(const std::vector<std::string> &args, e172::Context *) override;
};

} // namespace proj172::core

#endif // SELLWARETASK_H
