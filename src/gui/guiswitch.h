#ifndef GUISWITCH_H
#define GUISWITCH_H

#include <functional>

#include <src/gui/base/guimenuelement.h>


class GUISwitch : public GUIMenuElement {
private:
    std::function<void()> on;
    std::function<void()> off;
    bool enabled = false;

public:
    GUISwitch(std::function<void()> on = nullptr,  std::function<void()> off = nullptr);
    GUISwitch(std::string label, std::function<void()> on = nullptr,  std::function<void()> off = nullptr);
    GUISwitch(IInformative *informative, std::function<void()> on = nullptr,  std::function<void()> off = nullptr);

    // GUILabel interface
public:
    bool isSelectable() override;
    void enter() override;
};

#endif // GUISWITCH_H
