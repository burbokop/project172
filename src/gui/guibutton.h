#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <src/gui/base/guimenuelement.h>

#include <functional>

class GUIButton : public GUIMenuElement {
public:
    typedef std::function<void (const e172::Variant &)> f0;
    typedef std::function<void (const e172::ptr<Controller>&, const e172::Variant &)> f1;
    typedef std::function<void (e172::Context *, const e172::ptr<Controller>&, const e172::Variant &)> f2;
private:
    f0 m_f0;
    f1 m_f1;
    f2 m_f2;
public:
    GUIButton(const std::string &title, const f0& f);
    GUIButton(const std::string &title, const f1& f);
    GUIButton(const std::string &title, const f2& f);

    // GUIMenuElement interface
public:
    virtual bool isSelectable() override;
    virtual void enter(e172::Context *context) override;
};

#endif // GUIBUTTON_H
