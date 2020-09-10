#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <src/gui/base/guimenuelement.h>

#include <functional>

class GUIButton : public GUIMenuElement {
    std::function<void (const e172::Variant &)> m_clicked;
public:
    GUIButton(const std::string &title, const std::function<void(const e172::Variant&)>& clicked);

    // GUIMenuElement interface
public:
    virtual bool isSelectable() override;
    virtual void enter() override;
};

#endif // GUIBUTTON_H
