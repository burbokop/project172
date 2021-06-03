#ifndef BUYWARETASK_H
#define BUYWARETASK_H

#include "task.h"

#include <src/capabilities/warestorage.h>

#include <src/utility/option.h>


class BuyWareTask : public Task {
    e172::Option<std::string> m_targetWare = e172::None;
public:
    BuyWareTask(const e172::Option<std::string> &ware = e172::None);

    void dockingCompleated(const WareStorage::WareRef& wareRef);

    // Task interface
public:
    virtual void proceed(e172::Context *) override;
    virtual bool start(e172::Context *context) override;
    virtual void initFromCommand(const std::vector<std::string> &args, e172::Context *) override;
};

#endif // BUYWARETASK_H
