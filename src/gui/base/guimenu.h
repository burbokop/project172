#ifndef GUIMENU_H
#define GUIMENU_H

#include "guilistview.h"

#include <vector>
#include <functional>


class GUIMenu : public GUIListView {
protected:

    //GUIMenuElement *selectDown();
    //GUIMenuElement *selectUp();

private:
    std::vector<e172::ptr<GUIMenuElement>> m_menuElements;

public:
    GUIMenu() {};
    GUIMenu(std::string label);

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

#endif // GUIMENU_H
