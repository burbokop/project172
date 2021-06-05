#ifndef WARESTORAGE_H
#define WARESTORAGE_H

#include "capability.h"

#include <src/additional/ware/abstractwarecontainer.h>

#include <src/additional/pricetable.h>


class WareStorage : public Capability {
    mutable e172::ptr<AbstractWareContainer> m_wareContainer;
    e172::ptr<PriceTable> m_priceTable = new PriceTable();
protected:
    e172::ptr<AbstractWareContainer> wareContainer() const;
    virtual e172::ptr<AbstractWareContainer> createWareContainer() const = 0;
public:
    class WareRef {
        e172::ptr<WareStorage> m_storage;
        size_t m_index = 0;
    public:
        WareRef(const e172::ptr<WareStorage>& storage, size_t index);
        WareRef() {}
        size_t index() const;
        e172::ptr<WareStorage> storage() const;
        WareInfo info() const;
    };

    WareStorage();
    ~WareStorage();

    // Entity interface
public:
    size_t wareInfoCount() const;
    WareInfo wareInfo(size_t index) const;

    WareRef ref(size_t index) const;
    e172::Option<WareRef> findRef(const std::string &wareName) const;

    size_t amount() const;
    size_t capacity() const;

    size_t transferWareTo(size_t index, const e172::ptr<WareStorage> &destination, size_t count = std::numeric_limits<size_t>::max());
    e172::ptr<PriceTable> priceTable() const;

    e172::Option<size_t> indexOf(const std::string& wareName) const;

    std::list<std::string> prettyInfo() const;
};

class TransportWareStorage : public WareStorage {
    size_t m_initialCapacity = 0;
public:
    TransportWareStorage(size_t capacity = 0);
    size_t setCapacity(size_t capacity);

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override {};
    virtual void render(e172::AbstractRenderer *) override {};

    // WareStorage interface
protected:
    virtual e172::ptr<AbstractWareContainer> createWareContainer() const override;
};



class DebugTransportWareStorage : public WareStorage {
    size_t m_initialCapacity = 0;
    std::map<std::string, size_t> m_initialWares;
public:
    DebugTransportWareStorage(size_t capacity = 0, const std::map<std::string, size_t> &initialWares = {});
    size_t setCapacity(size_t capacity);
    e172::ptr<AbstractWareContainer> __wareContainer() const;

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override {};
    virtual void render(e172::AbstractRenderer *) override {};

    // WareStorage interface
protected:
    virtual e172::ptr<AbstractWareContainer> createWareContainer() const override;
};


#endif // WARESTORAGE_H
