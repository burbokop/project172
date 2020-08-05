#ifndef TEXTFORMAT_H
#define TEXTFORMAT_H

namespace e172 {

class TextFormat {
    int m_fontSize = 0;
public:
    TextFormat();
    TextFormat(int size);
    int fontSize() const;
};

}

#endif // TEXTFORMAT_H
