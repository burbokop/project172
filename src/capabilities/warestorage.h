#ifndef WARESTORAGE_H
#define WARESTORAGE_H

#include "capability.h"

#include <src/additional/ware/abstractwarecontainer.h>


class WareStorage : public Capability {
    AbstractWareContainer *m_wareContainer = nullptr;
protected:
    AbstractWareContainer *wareContainer() const;
    void setWareContainer(AbstractWareContainer *wareContainer);
public:
    WareStorage();
    ~WareStorage();

    // Entity interface
public:
    size_t wareInfoCount() const;
    WareInfo wareInfo(size_t index) const;

    size_t amount() const;
    size_t capacity() const;

    size_t transferWareTo(size_t index, WareStorage *storage, size_t count = std::numeric_limits<size_t>::max());
};

class TransportWareStorage : public WareStorage {
    // Entity interface
public:
    TransportWareStorage(size_t capacity = 0);
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override {};
    virtual void render(e172::AbstractRenderer *) override {};

    size_t setCapacity(size_t capacity);
};


#endif // WARESTORAGE_H
