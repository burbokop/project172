#ifndef PRICETABLE_H
#define PRICETABLE_H

#include <map>
#include <optional>
#include <src/object.h>


struct PriceTable : public e172::Object {
    class Price {
        std::optional<int64_t> m_buyPrice;
        std::optional<int64_t> m_sellPrice;
    public:
        Price(std::optional<int64_t> buyPrice, std::optional<int64_t> sellPrice);
        std::optional<int64_t> buyPrice() const;
        std::optional<int64_t> sellPrice() const;
        operator std::string() const;
        inline std::string toString() const { return *this; }
    };
private:
    std::map<std::string, std::pair<std::optional<int64_t>, std::optional<int64_t>>> m_data;
public:
    PriceTable();
    void setBuyPrice(const std::string& ware, int64_t price);
    void setSellPrice(const std::string& ware, int64_t price);
    void removeBuyPrice(const std::string& ware);
    void removeSellPrice(const std::string& ware);

    Price price(const std::string& ware) const;
    std::map<std::string, Price> priceMap() const;
};

#endif // PRICETABLE_H
