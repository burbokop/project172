QT -= core

CONFIG += c++17

INCLUDEPATH += klibcore

HEADERS += \
    $$PWD/src/kmacro.h \
    $$PWD/src/klibinfo.h \
    $$PWD/src/experimental/universalqueue/kuniversalqueue.h \
    $$PWD/src/utility/ktype.h \
    $$PWD/src/experimental/universalqueue/kcirclebuffer.h \
    $$PWD/src/experimental/universalqueue/kvoidhandle.h \
    $$PWD/src/utility/kmetafunction.h \
    $$PWD/src/memcontrol/kabstractfactory.h \
    $$PWD/src/memcontrol/kpull.h \
    $$PWD/src/memcontrol/kmoduleswitch.h


SOURCES += \
    $$PWD/src/experimental/universalqueue/kuniversalqueue.cpp \
    $$PWD/src/utility/ktype.cpp \
    $$PWD/src/experimental/universalqueue/kcirclebuffer.cpp \
    $$PWD/src/experimental/universalqueue/kvoidhandle.cpp \
    $$PWD/src/utility/kmetafunction.cpp \
    $$PWD/src/memcontrol/kabstractfactory.cpp \
    $$PWD/src/memcontrol/kpull.cpp \
    $$PWD/src/memcontrol/kmoduleswitch.cpp