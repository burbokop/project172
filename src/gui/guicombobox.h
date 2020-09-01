#ifndef GUICOMBOBOX_H
#define GUICOMBOBOX_H

#include "guichoice.h"

#include <src/gui/base/guicontainer.h>


template<typename T>
class GUIComboBox : public GUIContainer {
    std::list<T> m_list;
    int cmp_id = 0;
    int m_last_cmp_id = 0;
    std::function<void(T)> m_callback;
public:
    GUIComboBox(const std::string &title, const std::function<void(T)> &callback = std::function<void(T)>()) : GUIContainer(title) { m_callback = callback; }


    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override {
        if(m_last_cmp_id != cmp_id) {
            m_menuElements.clear();
            terminateChildren();
            for(const auto l : m_list) {
                addMenuElement(new GUIChoice(e172::Variant::fromValue<T>(l).toString(), e172::Variant(), [this, l](auto) {
                    if(m_callback)
                        m_callback(l);
                }));
            }
            m_last_cmp_id = cmp_id;
        }
    }

    std::list<T> list() const { return m_list; }

    void setList(std::list<T> list) {
        m_list = list;
        cmp_id++;
    }

    const std::function<void (T)> &callback() const {
        return m_callback;
    }

    void setCallback(const std::function<void (T)> &callback) {
        m_callback = callback;
    }
};

#endif // GUICOMBOBOX_H
