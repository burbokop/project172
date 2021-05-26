#ifndef GUIRADAR_H
#define GUIRADAR_H

#include <src/gui/base/guisingleelementlistview.h>

class Near;

class GUIRadar : public GUISingleElementListView {
    Near *m_near = nullptr;
public:
    GUIRadar(const std::string &title);

    Near *near() const;
    void setNear(Near *near);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::Variant rowModelData(int index) const override;
};

#endif // GUIRADAR_H
