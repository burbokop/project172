#include "pricetable.h"

PriceTable::PriceTable() {}

void PriceTable::setBuyPrice(const std::string &ware, int64_t price) {
    std::get<0>(m_data[ware]) = price;
}

void PriceTable::setSellPrice(const std::string &ware, int64_t price) {
    std::get<1>(m_data[ware]) = price;
}

void PriceTable::removeBuyPrice(const std::string &ware) {
    std::get<0>(m_data[ware]) = std::nullopt;
}

void PriceTable::removeSellPrice(const std::string &ware) {
    std::get<1>(m_data[ware]) = std::nullopt;
}

PriceTable::Price PriceTable::price(const std::string& ware) const {
    const auto it = m_data.find(ware);
    if(it != m_data.end()) {
        return Price(std::get<0>(it->second), std::get<1>(it->second));
    }
    return Price(std::nullopt, std::nullopt);
}

std::map<std::string, PriceTable::Price> PriceTable::priceMap() const {
    std::map<std::string, PriceTable::Price> result;
    for(const auto& a : m_data) {
        result.insert({ a.first, Price(std::get<0>(a.second), std::get<1>(a.second)) });
    }
    return result;
}

PriceTable::Price::Price(std::optional<int64_t> buyPrice, std::optional<int64_t> sellPrice) {
    m_buyPrice = buyPrice;
    m_sellPrice = sellPrice;
}

std::optional<int64_t> PriceTable::Price::buyPrice() const {
    return m_buyPrice;
}

std::optional<int64_t> PriceTable::Price::sellPrice() const {
    return m_sellPrice;
}

PriceTable::Price::operator std::string() const {
    return "bp: " + (m_buyPrice.has_value() ? std::to_string(m_buyPrice.value()) : "nl") + ", sp: " + (m_sellPrice.has_value() ? std::to_string(m_sellPrice.value()) : "nl");
}
