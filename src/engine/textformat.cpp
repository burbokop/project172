#include "textformat.h"


namespace e172 {

int TextFormat::fontSize() const
{
    return m_fontSize;
}

TextFormat::Alignment TextFormat::alignment() const
{
    return m_alignment;
}

TextFormat::Alignment operator |(TextFormat::Alignment a0, TextFormat::Alignment a1) {
    return static_cast<TextFormat::Alignment>(static_cast<int>(a0) | static_cast<int>(a1));
}

void TextFormat::setAlignment(const Alignment &alignment)
{
    m_alignment = alignment;
}

void TextFormat::setFontSize(int fontSize)
{
    m_fontSize = fontSize;
}

Font TextFormat::font() const
{
    return m_font;
}

void TextFormat::setFont(const Font &font)
{
    m_font = font;
}

TextFormat::TextFormat() {
    
}

TextFormat::TextFormat(TextFormat::Alignment alignment) {
    m_alignment = alignment;
}

TextFormat::TextFormat(TextFormat::Alignment alignment, int size) {
    m_alignment = alignment;
    m_fontSize = size;
}

}
