#include "textformat.h"


using namespace e172;
int TextFormat::fontSize() const
{
    return m_fontSize;
}

TextFormat::TextFormat() {

}

TextFormat::TextFormat(int size) {
    m_fontSize = size;
}
