#include "debug.h"

#include <iostream>

namespace e172 {



std::function<void(const std::string &, Debug::MessageType)> Debug::m_proceedMessage = [](const std::string &data, Debug::MessageType type){
    if(type == Debug::PrintMessage) {
        std::cout << data << std::endl;
    } else if(type == Debug::WarningMessage) {
        std::cout << "\033[33m" << data << "\033[0m" << std::endl;
    } else if(type == Debug::FatalMessage) {
        std::cout << "\033[31m" << data << "\033[0m" << std::endl;
    }
};

std::string Debug::m_separator = " ";

void Debug::setSeparator(const std::string &separator) {
    m_separator = separator;
}

void Debug::installHandler(const std::function<void (const std::string &, Debug::MessageType)> &handler) {
    m_proceedMessage = handler;
}



}
