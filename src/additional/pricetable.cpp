#include "pricetable.h"

PriceTable::PriceTable() {}

void PriceTable::setBuyPrice(const std::string &ware, int64_t price) {
    std::get<0>(m_data[ware]) = price;
}

void PriceTable::setSellPrice(const std::string &ware, int64_t price) {
    std::get<1>(m_data[ware]) = price;
}

void PriceTable::removeBuyPrice(const std::string &ware) {
    std::get<0>(m_data[ware]) = e172::None;
}

void PriceTable::removeSellPrice(const std::string &ware) {
    std::get<1>(m_data[ware]) = e172::None;
}

e172::Option<std::string> PriceTable::findWithBuyPrice() {
    for(const auto& d : m_data) {
        if(std::get<0>(d.second).isDefined()) {
            return d.first;
        }
    }
    return e172::None;
}

e172::Option<std::string> PriceTable::findWithSellPrice() {
    for(const auto& d : m_data) {
        if(std::get<1>(d.second).isDefined()) {
            return d.first;
        }
    }
    return e172::None;
}

PriceTable::Price PriceTable::price(const std::string& ware) const {
    const auto it = m_data.find(ware);
    if(it != m_data.end()) {
        return Price(std::get<0>(it->second), std::get<1>(it->second));
    }
    return Price(e172::None, e172::None);
}

std::map<std::string, PriceTable::Price> PriceTable::priceMap() const {
    std::map<std::string, PriceTable::Price> result;
    for(const auto& a : m_data) {
        result.insert({ a.first, Price(std::get<0>(a.second), std::get<1>(a.second)) });
    }
    return result;
}

PriceTable::Price::Price(const e172::Option<int64_t> &buyPrice, const e172::Option<int64_t> &sellPrice) {
    m_buyPrice = buyPrice;
    m_sellPrice = sellPrice;
}

e172::Option<int64_t> PriceTable::Price::buyPrice() const {
    return m_buyPrice;
}

e172::Option<int64_t> PriceTable::Price::sellPrice() const {
    return m_sellPrice;
}

PriceTable::Price::operator std::string() const {
    return "{ buy: " + m_buyPrice.toString() + ", sell: " + m_sellPrice.toString() + " }";
}
