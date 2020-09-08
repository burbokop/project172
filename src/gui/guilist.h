#ifndef GUILIST_H
#define GUILIST_H


#include <src/gui/base/guicontainer.h>

#include <src/near.h>


class GUIList : public GUIContainer {
private:
    Near *m_near = nullptr;

    virtual GUIMenuElement *forEach(Unit *unit);

    std::vector<GUIMenuElement *> informativeToElements(std::list<Entity *> array);

    void onChoice(e172::Variant value);

public:
    GUIList(std::string label);
    GUIList(IInformative *informative);


    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
    Near *near() const;
    void setNear(Near *near);
};

#endif // GUILIST_H
