#ifndef BUYWARETASK_H
#define BUYWARETASK_H

#include "task.h"

#include <src/capabilities/warestorage.h>

#include <src/utility/option.h>

namespace proj172::core {

class BuyWareTask : public Task {
    e172::Option<std::string> m_targetWare = e172::None;
public:
    BuyWareTask(const e172::Option<std::string> &ware = e172::None);

    void dockingCompleated(const WareStorage::WareRef& wareRef);

    class Result {
        e172::Option<std::string> m_targetWare;
        bool m_ok = false;
    public:
        Result(e172::Option<std::string> targetWare = e172::None, bool ok = false);
        bool ok() const;
        e172::Option<std::string> targetWare() const;
        e172::Variant toVariant() const;
    };

    // Task interface
public:
    virtual void proceed(e172::Context *) override;
    virtual bool start(e172::Context *context) override;
    virtual void initFromCommand(const std::vector<std::string> &args, e172::Context *) override;
};

} // namespace proj172::core

#endif // BUYWARETASK_H
