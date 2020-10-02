#ifndef GUILISTVIEW_H
#define GUILISTVIEW_H

#include "guimenuelement.h"
#include "guistack.h"



class GUIListView : public GUIMenuElement {
    GUIStack *m_stack = nullptr;
    int m_selectedIndex = 0;
    int m_verticalInterval = 24;
    std::vector<double> xOffsets;
    double titleXOffset = 0;
public:
    GUIListView() {}
    GUIListView(const std::string &title);

    GUIStack *stack() const;
    void setStack(GUIStack *stack);
    int verticalInterval() const;
    void setVerticalInterval(int verticalInterval);

    virtual int rowCount() const = 0;
    virtual std::string rowText(int index) const = 0;
    virtual GUIMenuElement *rowElement(int index) const = 0;
    virtual e172::Variant rowModelData(int index) const = 0;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;

    // GUIMenuElement interface
public:
    virtual bool isSelectable() override;
    virtual bool hasSubElements() override;


};

#endif // GUILISTVIEW_H
