#pragma once

#include "base/guilistview.h"
#include "guibutton.h"

namespace proj172::core {

template<typename T>
class GUIComboBox : public GUIListView {
    std::vector<T> m_data;
    std::function<void(T)> m_callback;
    std::unique_ptr<GUIButton> m_button = e172::FactoryMeta::makeUniq<GUIButton>("", [this](auto md) {
        onEnter(md.toInt());
    });

    void onEnter(int index) {
        if(m_callback && index < m_data.size() && index >= 0)
            m_callback(m_data[index]);
    }
public:
    GUIComboBox(e172::FactoryMeta &&meta,
                const std::string &title,
                const std::function<void(T)> &callback = std::function<void(T)>())
        : GUIListView(std::move(meta), title)
    {
        m_callback = callback;
    }
    // Entity interface
public:
    std::vector<T> data() const { return m_data; }
    void setData(const std::vector<T> &vector) { m_data = vector; }
    void setList(const std::list<T> &list) { m_data = std::vector<T>(list.begin(), list.end()); }
    const std::function<void (T)> &callback() const { return m_callback; }
    void setCallback(const std::function<void (T)> &callback) { m_callback = callback; }

    // GUIListView interface
public:
    virtual int rowCount() const override { return m_data.size(); }
    virtual std::string rowText(int index) const override { return m_data[index]; };
    virtual e172::ptr<GUIMenuElement> rowElement(int) const override { return m_button.get(); };
    virtual e172::Variant rowModelData(int index) const override { return index; };
};

} // namespace proj172::core

