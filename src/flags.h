#pragma once

#include <e172/utility/flagparser.h>
#include <ostream>

namespace proj172 {

enum class AppMode { Server, Client, Both, Mock, Old };

inline std::ostream &operator<<(std::ostream &stream, AppMode m)
{
    switch (m) {
    case AppMode::Server:
        return stream << "Server";
    case AppMode::Client:
        return stream << "Client";
    case AppMode::Both:
        return stream << "Both";
    case AppMode::Mock:
        return stream << "Mock";
    case AppMode::Old:
        return stream << "Old";
    }
}

e172::Either<e172::FlagParseError, AppMode> operator>>(e172::RawFlagValue &flag,
                                                       e172::TypeTag<AppMode>);

struct Flags
{
    AppMode mode;
    bool displayChart;

    /**
     * @brief parseOrDie - parse command line flags or end application on error
     * @param argc
     * @param argv
     * @return 
     */
    static Flags parseOrDie(int argc, const char **argv);
};

inline std::ostream &operator<<(std::ostream &stream, const Flags &f)
{
    return stream << "{ mode: " << f.mode << " }";
}

} // namespace proj172
