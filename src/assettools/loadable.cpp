#include "loadable.h"



std::string Loadable::className() const {
    return m_className;
}

std::string Loadable::loadableId() const
{
    return m_loadableId;
}

Loadable::Loadable() {}

Loadable::~Loadable() {}
