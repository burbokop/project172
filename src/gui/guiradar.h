#ifndef GUIRADAR_H
#define GUIRADAR_H

#include <src/gui/base/guilistview.h>


class Near;

class GUIRadar : public GUIListView {
    Near *m_near = nullptr;

    GUIMenuElement *m_rowElement = nullptr;
public:
    GUIRadar(const std::string &title);

    Near *near() const;
    void setNear(Near *near);
    void setRowElement(GUIMenuElement *rowElement);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual GUIMenuElement *rowElement(int) const override;
    virtual e172::Variant rowModelData(int index) const override;

};

#endif // GUIRADAR_H
