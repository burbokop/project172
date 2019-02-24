#ifndef FRAMEBUILDER_H
#define FRAMEBUILDER_H

#include <vector>

class FrameBuilder {
public:

    static std::vector<char> cover(std::vector<char> data);
    static std::vector<char> uncover(std::vector<char> frame);

};

#endif // FRAMEBUILDER_H
