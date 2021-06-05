#ifndef WARECONTAINER_H
#define WARECONTAINER_H

#include <string>
#include <vector>

#include "abstractwarecontainer.h"

#include <variant>

class WareContainer : public AbstractWareContainer {
    std::vector<std::tuple<std::string, size_t>> m_data;
    size_t m_capacity = 0;
public:
    struct all_allowed_t {};
    static inline all_allowed_t AllAllowed;
    typedef std::variant<std::vector<std::string>, all_allowed_t> Allowed;
private:
    Allowed m_allowedInput = std::vector<std::string>();
    Allowed m_allowedOutput = std::vector<std::string>();
public:
    virtual size_t wareAwailableAdditingAmount(std::string ware, size_t count, bool ignoreAllowed) override;
    virtual size_t wareAwailableRemovingAmount(size_t index, size_t count, bool ignoreAllowed = false) override;
    virtual size_t addWare(std::string ware, size_t count, bool ignoreAllowed = false) override;
    virtual size_t removeWare(size_t index, size_t count, bool ignoreAllowed = false) override;
    virtual size_t wareInfoCount() const override;
    virtual WareInfo wareInfo(size_t index) const override;
    virtual size_t amount() const override;
    virtual size_t capacity() const override;

    double full() const;

    WareContainer(size_t capacity = 0);
    size_t setCapacity(const size_t &capacity);


    bool isInputAllowed(const std::string &wareName) const;
    bool isOutputAllowed(const std::string &wareName) const;
    Allowed allowedInput() const;
    void setAllowedInput(const Allowed &allowedInput);
    Allowed allowedOutput() const;
    void setAllowedOutput(const Allowed &allowedOutput);

    bool isAllInputAllowed() const;
    bool isAllOutputAllowed() const;
    bool isNoInputAllowed() const;
    bool isNoOutputAllowed() const;

};

std::ostream &operator<<(std::ostream &stream, const WareContainer::Allowed& allowed);

#endif // WARECONTAINER_H
