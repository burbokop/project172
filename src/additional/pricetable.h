#ifndef PRICETABLE_H
#define PRICETABLE_H

#include <optional>
#include <vector>

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
    std::vector<std::pair<std::optional<int64_t>, std::optional<int64_t>>> m_data;
public:
    PriceTable();
    void setBuyPrice(size_t index, int64_t price);
    void setSellPrice(size_t index, int64_t price);
    void removeBuyPrice(size_t index);
    void removeSellPrice(size_t index);

    Price price(size_t index) const;
};

#endif // PRICETABLE_H
