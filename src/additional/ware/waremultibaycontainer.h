#ifndef WAREMULTIBAYCONTAINER_H
#define WAREMULTIBAYCONTAINER_H

#include "warecontainer.h"

class WareMultiBayContainer : public AbstractWareContainer {
    std::vector<WareContainer> m_data;
public:
    WareMultiBayContainer(const std::vector<WareContainer> &data = std::vector<WareContainer>());
    inline WareContainer &operator[](size_t i) { return m_data[i]; };
    inline WareContainer operator[](size_t i) const { return m_data[i]; };
    inline size_t size() const { return m_data.size(); };
    void setBayCount(size_t count);

    // AbstractWareContainer interface
public:
    virtual size_t wareAwailableAdditingAmount(std::string ware, size_t count, bool ignoreAllowed) override;
    virtual size_t wareAwailableRemovingAmount(size_t index, size_t count, bool ignoreAllowed) override;
    virtual size_t addWare(std::string ware, size_t count, bool ignoreAllowed = false) override;
    virtual size_t removeWare(size_t index, size_t count, bool ignoreAllowed = false) override;
    virtual size_t wareInfoCount() const override;
    virtual WareInfo wareInfo(size_t index) const override;
    virtual size_t amount() const override;
    virtual size_t capacity() const override;

};

#endif // WAREMULTIBAYCONTAINER_H
