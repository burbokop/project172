#include "warestorage.h"

#include <src/additional/ware/warecontainer.h>



e172::ptr<AbstractWareContainer> WareStorage::wareContainer() const {
    if(!m_wareContainer.data()) {
        m_wareContainer = createWareContainer();
    }
    return m_wareContainer;
}

WareStorage::WareStorage() {}

WareStorage::~WareStorage() {
    if(wareContainer()) {
        if(wareContainer()->liveInHeap())
            delete wareContainer().data();
    }
}

size_t WareStorage::wareInfoCount() const {
    if(wareContainer())
        return wareContainer()->wareInfoCount();

    return 0;
}

WareInfo WareStorage::wareInfo(size_t index) const {
    if(wareContainer())
        return wareContainer()->wareInfo(index);

    return WareInfo("", 0);
}

size_t WareStorage::amount() const {
    if(wareContainer())
        return wareContainer()->amount();

    return 0;
}

size_t WareStorage::capacity() const {
    if(wareContainer())
        return wareContainer()->capacity();

    return 0;
}

size_t WareStorage::transferWareTo(size_t index, const e172::ptr<WareStorage>& storage, size_t count) {
    if(wareContainer() && storage->wareContainer()) {
        return wareContainer()->transferWareTo(index, storage->wareContainer(), count);
    }
    return 0;
}

TransportWareStorage::TransportWareStorage(size_t capacity) {
    m_initialCapacity = capacity;
}

size_t TransportWareStorage::setCapacity(size_t capacity) {
    return e172::smart_cast<WareContainer>(wareContainer())->setCapacity(capacity);
}

e172::ptr<AbstractWareContainer> TransportWareStorage::createWareContainer() const {
    auto wc = new WareContainer(m_initialCapacity);
    wc->setAllowedInput(WareContainer::AllAllowed);
    wc->setAllowedOutput(WareContainer::AllAllowed);
    return wc;
}

DebugTransportWareStorage::DebugTransportWareStorage(size_t capacity, const std::map<std::string, size_t> &initialWares) {
    m_initialCapacity = capacity;
    m_initialWares = initialWares;
}

size_t DebugTransportWareStorage::setCapacity(size_t capacity) {
    return e172::smart_cast<WareContainer>(wareContainer())->setCapacity(capacity);
}

e172::ptr<AbstractWareContainer> DebugTransportWareStorage::__wareContainer() const {
    return wareContainer();
}

e172::ptr<AbstractWareContainer> DebugTransportWareStorage::createWareContainer() const {
    auto wc = new WareContainer(m_initialCapacity);
    wc->setAllowedInput(WareContainer::AllAllowed);
    wc->setAllowedOutput(WareContainer::AllAllowed);
    for(const auto& w : m_initialWares) {
        wc->addWare(w.first, w.second);
    }
    return wc;
}

size_t WareStorage::WareRef::index() const {
    return m_index;
}

e172::ptr<WareStorage> WareStorage::WareRef::storage() const {
    return m_storage;
}

WareStorage::WareRef::WareRef(const e172::ptr<WareStorage> &storage, size_t index) {
    m_storage = storage;
    m_index = index;
}
