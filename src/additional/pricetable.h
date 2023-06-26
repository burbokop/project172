#pragma once

#include <map>
#include <optional>
#include <src/object.h>
#include <src/utility/option.h>

namespace proj172::core {

struct PriceTable : public e172::Object {
    class Price {
        e172::Option<int64_t> m_buyPrice;
        e172::Option<int64_t> m_sellPrice;
    public:
        Price(const e172::Option<int64_t>& buyPrice, const e172::Option<int64_t>& sellPrice);
        e172::Option<int64_t> buyPrice() const;
        e172::Option<int64_t> sellPrice() const;
        operator std::string() const;
        inline std::string toString() const { return *this; }
    };
private:
    std::map<std::string, std::pair<e172::Option<int64_t>, e172::Option<int64_t>>> m_data;
public:
    PriceTable() = default;
    void setBuyPrice(const std::string& ware, int64_t price);
    void setSellPrice(const std::string& ware, int64_t price);
    void removeBuyPrice(const std::string& ware);
    void removeSellPrice(const std::string& ware);

    e172::Option<std::string> findWithBuyPrice();
    e172::Option<std::string> findWithSellPrice();

    Price price(const std::string& ware) const;
    std::map<std::string, Price> priceMap() const;
};

} // namespace proj172::core
