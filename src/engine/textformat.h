#ifndef TEXTFORMAT_H
#define TEXTFORMAT_H

namespace e172 {

typedef int Font;

class TextFormat {
    int m_fontSize = 0;
    Font m_font = -1;
public:
    enum Alignment {
        AlignHCenter = 1,
        AlignVCenter = 2,
        AlignLeft = 4,
        AlignRight = 8,
        AlignTop = 16,
        AlignBottom = 32,
        AlignCenter = AlignHCenter | AlignVCenter,
        AlignDefault = AlignRight | AlignBottom
    };

    friend Alignment operator |(Alignment a0, Alignment a1);
private:
    Alignment m_alignment = AlignRight | AlignBottom;
public:
    TextFormat();
    TextFormat(Alignment alignment);
    TextFormat(Alignment alignment, int size);
    int fontSize() const;
    Alignment alignment() const;
    void setAlignment(const Alignment &alignment);
    void setFontSize(int fontSize);
    Font font() const;
    void setFont(const Font &font);
};

}

#endif // TEXTFORMAT_H
