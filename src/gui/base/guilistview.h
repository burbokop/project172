#ifndef GUILISTVIEW_H
#define GUILISTVIEW_H

#include "guimenuelement.h"
#include "guistack.h"



class GUIListView : public GUIMenuElement {
    GUIStack *m_stack = nullptr;
    int m_selectedIndex = -1;
    int m_verticalInterval = 24;
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

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;

    // GUIMenuElement interface
public:
    virtual bool isSelectable() override;
    virtual bool hasSubElements() override;


};

#endif // GUILISTVIEW_H
