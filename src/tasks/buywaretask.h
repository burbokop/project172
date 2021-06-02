#ifndef BUYWARETASK_H
#define BUYWARETASK_H

#include "task.h"

#include <src/capabilities/warestorage.h>


class BuyWareTask : public Task {
    std::string m_targetWare;
public:
    BuyWareTask(const std::string &ware = "");

    void dockingCompleated(const WareStorage::WareRef& wareRef);

    // Task interface
public:
    virtual void proceed(e172::Context *) override;
    virtual bool start(e172::Context *context) override;
    virtual void initFromCommand(const std::vector<std::string> &args, e172::Context *) override;
};

#endif // BUYWARETASK_H
