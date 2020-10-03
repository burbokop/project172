#ifndef GUICOMBOBOX_H
#define GUICOMBOBOX_H

#include "guibutton.h"

#include <src/gui/base/guilistview.h>

template<typename T>
class GUIComboBox : public GUIListView {
    std::vector<T> m_data;
    std::function<void(T)> m_callback;
    GUIButton *button = new GUIButton("", [this](auto md){ onEnter(md.toInt()); });

    void onEnter(int index) {
        if(m_callback && index < m_data.size() && index >= 0)
            m_callback(m_data[index]);
    }
public:
    GUIComboBox(const std::string &title, const std::function<void(T)> &callback = std::function<void(T)>()) : GUIListView(title) { m_callback = callback; }
    ~GUIComboBox() { delete button; }
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
    virtual GUIMenuElement *rowElement(int) const override { return button; };
    virtual e172::Variant rowModelData(int index) const override { return index; };
};

#endif // GUICOMBOBOX_H
