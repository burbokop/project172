#include "flags.h"

#include <config/project.h>
#include <iostream>

proj172::Flags proj172::Flags::parseOrDie(int argc, const char **argv)
{
    return e172::FlagParser::parse<Flags>(
               argc,
               argv,
               [](e172::FlagParser &p) {
                   return Flags{.mode = p.flag(
                                    e172::OptFlag<AppMode>{.shortName = "m",
                                                           .longName = "mode",
                                                           .description
                                                           = "Application mode [server, "
                                                             "client, both=default, mock, old]",
                                                           .defaultVal = AppMode::Both}),
                                .displayChart = p.flag<bool>(
                                    e172::Flag{.shortName = "display-chart",
                                               .longName = "c",
                                               .description = "Display chart"})};
               },
               [](const e172::FlagParser &p) {
                   p.displayErr(std::cerr);
                   std::exit(1);
               },
               [](const e172::FlagParser &p) {
                   p.displayHelp(std::cout);
                   std::exit(0);
               },
               [](const e172::FlagParser &p) {
                   p.displayVersion(std::cout, PROJECT_VER);
                   std::exit(0);
               })
        .value();
}

e172::Either<e172::FlagParseError, proj172::AppMode> proj172::operator>>(e172::RawFlagValue &flag,
                                                                         e172::TypeTag<AppMode>)
{
    if (flag.str == "server") {
        return e172::Right(AppMode::Server);
    } else if (flag.str == "client") {
        return e172::Right(AppMode::Client);
    } else if (flag.str == "both") {
        return e172::Right(AppMode::Both);
    } else if (flag.str == "mock") {
        return e172::Right(AppMode::Mock);
    } else if (flag.str == "old") {
        return e172::Right(AppMode::Old);
    } else {
        return e172::Left(e172::FlagParseError::EnumValueNotFound);
    }
}
