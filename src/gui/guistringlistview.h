#ifndef GUISTRINGLISTVIEW_H
#define GUISTRINGLISTVIEW_H

#include <src/gui/base/guilistview.h>



class GUIStringListView : public GUIListView {
    std::vector<std::string> m_data;
public:

    GUIStringListView(const std::string &title, const std::vector<std::string>& data) : GUIListView(title) { m_data = data; }

    template<typename T>
    GUIStringListView(const std::string &title, const T& container) : GUIListView(title) {
        m_data.resize(container.size());
        int i = 0;
        for(auto a : container)
            m_data[i++] = a;
    }

    std::vector<std::string> data() const;
    void setData(const std::vector<std::string> &data);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::ptr<GUIMenuElement> rowElement(int) const override;
    virtual e172::Variant rowModelData(int) const override;

};

#endif // GUISTRINGLISTVIEW_H
