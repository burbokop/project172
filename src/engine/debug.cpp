#include "debug.h"


namespace e172 {



std::function<void(const std::string &, Debug::MessageType)> Debug::m_proceedMessage;
std::string Debug::m_separator = " ";

void Debug::setSeparator(const std::string &separator) {
    m_separator = separator;
}

void Debug::installHandler(const std::function<void (const std::string &, Debug::MessageType)> &handler) {
    m_proceedMessage = handler;
}



}
