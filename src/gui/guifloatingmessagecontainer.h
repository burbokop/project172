#pragma once

#include "base/guicontainer.h"
#include "guicentralmessage.h"
#include "guifloatingmessage.h"

namespace proj172::core {

//DEPRECATED (use GUIContainer and create new Floating)
class GUIFloatingMessageContainer : public GUIElement {
public:
    GUIFloatingMessageContainer(e172::FactoryMeta &&meta)
        : GUIElement(std::move(meta))
    {}

    void addFloatingMessage(const e172::ptr<Unit> &unit, std::string message);
    void addBlushingFloatingMessage(const e172::ptr<Unit> &unit, int value);
    void addCommonFloatingMessage(e172::Context *context, const e172::Variant &value);

    void setMessage(GUICentralMessage *value);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *) override {}

private:
    static const unsigned FLOATING_LIFE_TIME;

    GUICentralMessage *m_centralMessage = nullptr;
    GUIFloatingMessage *m_floatingMessage = nullptr;
    e172::ElapsedTimer m_floatingMessageLifeTimer = e172::ElapsedTimer(FLOATING_LIFE_TIME);
};

} // namespace proj172::core
