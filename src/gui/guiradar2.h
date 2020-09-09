#ifndef GUIRADAR2_H
#define GUIRADAR2_H

#include <src/gui/base/guilistview.h>


class Near;

class GUIRadar2 : public GUIListView {
    Near *m_near = nullptr;

    GUIMenuElement *m_rowElement = nullptr;
public:
    GUIRadar2(const std::string &title);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual GUIMenuElement *rowElement(int index) const override;
    Near *near() const;
    void setNear(Near *near);
    void setRowElement(GUIMenuElement *rowElement);
};

#endif // GUIRADAR2_H
