#ifndef ABSTRACTWARECONTAINER_H
#define ABSTRACTWARECONTAINER_H


#include <string>
#include <vector>

#include <src/object.h>

#include <src/utility/ptr.h>


class WareInfo {
    std::string m_wareName;
    size_t m_count = 0;
public:
    WareInfo(const std::string &name, size_t count);

    std::string wareName() const;
    size_t count() const;

    operator std::string() const;
    inline std::string toString() const { return *this; }
};

std::ostream &operator<<(std::ostream& stream, const WareInfo& info);

class AbstractWareContainer : public e172::Object {
public:
    AbstractWareContainer();

    virtual size_t wareAwailableAdditingAmount(std::string ware, size_t count, bool ignoreAllowed = false) = 0;
    virtual size_t wareAwailableRemovingAmount(size_t index, size_t count, bool ignoreAllowed = false) = 0;

    virtual size_t addWare(std::string ware, size_t count, bool ignoreAllowed = false) = 0;
    virtual size_t removeWare(size_t index, size_t count, bool ignoreAllowed = false) = 0;

    virtual size_t wareInfoCount() const = 0;
    virtual WareInfo wareInfo(size_t index) const = 0;

    virtual size_t amount() const = 0;
    virtual size_t capacity() const = 0;

    size_t transferWareTo(size_t index, const e172::ptr<AbstractWareContainer>& container, size_t count = std::numeric_limits<size_t>::max());

    virtual ~AbstractWareContainer() {}
};

#endif // ABSTRACTWARECONTAINER_H
