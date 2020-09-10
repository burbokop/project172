#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include "guilistview.h"

#include <vector>
#include <functional>


class GUIContainer : public GUIListView {
protected:

    //GUIMenuElement *selectDown();
    //GUIMenuElement *selectUp();

private:
    std::vector<GUIMenuElement*> m_menuElements;

public:
    GUIContainer() {};
    GUIContainer(std::string label);

    void addMenuElement(GUIMenuElement *element);
    void removeMenuElement(GUIMenuElement *element);
    void clearElements();
    void terminateElements();

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual GUIMenuElement *rowElement(int index) const override;
};

#endif // GUICONTAINER_H
