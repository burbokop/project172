#ifndef DEBUG_H
#define DEBUG_H


#include <sstream>
#include <functional>

namespace e172 {


class Debug {
public:
    enum MessageType {
        PrintMessage,
        WarningMessage,
        FatalMessage
    };
private:

    static std::function<void(const std::string &, MessageType)> m_proceedMessage;
    static std::string m_separator;
public:
    static void installHandler(const std::function<void(const std::string &, MessageType)> &handler);
    static void setSeparator(const std::string &separator);


    template <typename Separator, typename Arg, typename... Args>
    static void passArgsToStream(std::ostream& out, const Separator &separator, const Arg& arg, const Args& ...args) {
        out << arg;
        ((out << separator << args), ...);
    }


    template<typename Arg, typename ...Args>
    static void emitMessage(MessageType type, const Arg& arg, const Args& ...args) {
        if(m_proceedMessage) {
            std::stringstream ss;
            passArgsToStream(ss, m_separator, arg, args...);
            m_proceedMessage(ss.str(), type);
        }
    }


    template<typename Arg, typename ...Args>
    static void print(const Arg& arg, const Args& ...args) {
        emitMessage(PrintMessage, arg, args...);
    }

    template<typename Arg, typename ...Args>
    static void warning(const Arg& arg, const Args& ...args) {
        emitMessage(WarningMessage, arg, args...);
    }

    template<typename Arg, typename ...Args>
    static void fatal(const Arg& arg, const Args& ...args) {
        emitMessage(FatalMessage, arg, args...);
    }

};

}
#endif // DEBUG_H
