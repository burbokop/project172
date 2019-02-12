#include "framebuilder.h"


std::vector<char> FrameBuilder::cover(std::vector<char> data) {
    std::vector<char> frame;
    char checksum = 0;

    frame.push_back(0x7E);
    for (char c : data) {
        checksum += c;
        if (c == 0x7E || c == 0x7D) {
            frame.push_back(0x7D);
            c ^= 0x40;
        }
        frame.push_back(c);
    }

    char covered_checksum = -checksum;
    if (covered_checksum == 0x7E || covered_checksum == 0x7D) {
        frame.push_back(0x7D);
        covered_checksum ^= 0x40;
    }
    frame.push_back(covered_checksum);
    frame.push_back(0x7E);

    return frame;
}

std::vector<char> FrameBuilder::uncover(std::vector<char> frame) {
    std::vector<char> result;
    char checksum = 0;
    bool checkNext = false;
    int i = 0;
    for(char c : frame) {
        if (c == 0x7E) {
            if (i >= 2) {
                // && checksum == 0
                result.resize(result.size() - 1);
                return result;
            }
        } else if(c == 0x7D) {
            checkNext = true;
        } else {
            if(checkNext) {
                if(c == 0x3D) result.push_back(0x7D);
                else if(c == 0x3E) result.push_back(0x7E);
            } else {
                result.push_back(c);
            }

            checksum += c;
        }
        checkNext = false;
        i++;
    }
    return std::vector<char>();
}
