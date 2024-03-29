#ifndef GUIMENU_H
#define GUIMENU_H

#include "guilistview.h"
#include <vector>
#include <functional>

namespace proj172::core {

class GUIMenu : public GUIListView {
protected:

    //GUIMenuElement *selectDown();
    //GUIMenuElement *selectUp();

private:
    std::vector<e172::ptr<GUIMenuElement>> m_menuElements;

public:
    GUIMenu(e172::FactoryMeta &&meta)
        : GUIListView(std::move(meta)){};

    GUIMenu(e172::FactoryMeta &&meta, std::string label)
        : GUIListView(std::move(meta), label)
    {}

    void addMenuElement(const e172::ptr<GUIMenuElement> &element);
    void removeMenuElement(const e172::ptr<GUIMenuElement> &element);
    void clearElements();
    void terminateElements();

    e172::ptr<GUIMenu> withMenuChildren(const std::list<e172::ptr<GUIMenuElement>>& children);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::ptr<GUIMenuElement> rowElement(int index) const override;
    virtual e172::Variant rowModelData(int) const override;
};

} // namespace proj172::core

#endif // GUIMENU_H
