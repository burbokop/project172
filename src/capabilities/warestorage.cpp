#include "warestorage.h"

#include <src/additional/ware/warecontainer.h>

void WareStorage::setWareContainer(AbstractWareContainer *wareContainer) {
    m_wareContainer = wareContainer;
}

AbstractWareContainer *WareStorage::wareContainer() const {
    return m_wareContainer;
}

WareStorage::WareStorage() {}

WareStorage::~WareStorage() {
    if(m_wareContainer) {
        if(m_wareContainer->liveInHeap())
            delete m_wareContainer;
    }
}

size_t WareStorage::wareInfoCount() const {
    if(m_wareContainer)
        return m_wareContainer->wareInfoCount();

    return 0;
}

WareInfo WareStorage::wareInfo(size_t index) const {
    if(m_wareContainer)
        return m_wareContainer->wareInfo(index);

    return WareInfo("", 0);
}

size_t WareStorage::amount() const {
    if(m_wareContainer)
        return m_wareContainer->amount();

    return 0;
}

size_t WareStorage::capacity() const {
    if(m_wareContainer)
        return m_wareContainer->capacity();

    return 0;
}

size_t WareStorage::transferWareTo(size_t index, WareStorage *storage, size_t count) {
    if(m_wareContainer && storage->m_wareContainer) {
        return m_wareContainer->transferWareTo(index, storage->m_wareContainer, count);
    }
    return 0;
}

TransportWareStorage::TransportWareStorage(size_t capacity) {
    auto wc = new WareContainer(capacity);
    wc->setAllowedInput(WareContainer::AllAllowed);
    setWareContainer(wc);
}

size_t TransportWareStorage::setCapacity(size_t capacity) {
    return dynamic_cast<WareContainer*>(wareContainer())->setCapacity(capacity);
}
