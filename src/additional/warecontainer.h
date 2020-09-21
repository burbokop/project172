#ifndef WARECONTAINER_H
#define WARECONTAINER_H

#include <string>
#include <vector>


class WareInfo {
    std::string m_wareName;
    size_t m_count = 0;
public:
    WareInfo(const std::string &name, size_t count);

    std::string wareName() const;
    size_t count() const;
};

class WareContainer {
    std::vector<std::pair<std::string, size_t>> m_data;
    size_t m_capacity = 0;

protected:
    size_t addWare(std::string ware, size_t count);
    size_t removeWare(size_t index, size_t count);
    void setCapacity(const size_t &capacity);
public:
    WareContainer(size_t capacity);
    size_t wareInfoCount() const;
    WareInfo wareInfo(size_t index) const;

    size_t amount() const;
    size_t capacity() const;

    size_t transferWareTo(size_t index, WareContainer *container, size_t count = std::numeric_limits<size_t>::max());

};

#endif // WARECONTAINER_H
