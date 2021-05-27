#include "pricetable.h"

PriceTable::PriceTable() {}

void PriceTable::setBuyPrice(size_t index, int64_t price) {
    if(index >= m_data.size()) {
        m_data.resize(index + 1);
    }
    std::get<0>(m_data[index]) = price;
}

void PriceTable::setSellPrice(size_t index, int64_t price) {
    if(index >= m_data.size()) {
        m_data.resize(index + 1);
    }
    std::get<1>(m_data[index]) = price;
}

void PriceTable::removeBuyPrice(size_t index) {
    if(index >= m_data.size()) {
        m_data.resize(index + 1);
    }
    std::get<0>(m_data[index]) = std::nullopt;
}

void PriceTable::removeSellPrice(size_t index) {
    if(index >= m_data.size()) {
        m_data.resize(index + 1);
    }
    std::get<1>(m_data[index]) = std::nullopt;
}

PriceTable::Price PriceTable::price(size_t index) const {
    if(index < m_data.size()) {
        return Price(std::get<0>(m_data[index]), std::get<1>(m_data[index]));
    }
    return Price(std::nullopt, std::nullopt);
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
    return (m_buyPrice.has_value() ? std::to_string(m_buyPrice.value()) : "nl") + ", " + (m_sellPrice.has_value() ? std::to_string(m_sellPrice.value()) : "nl");
}
