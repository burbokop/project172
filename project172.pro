QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -ljsoncpp \
        -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSDL2_mixer

SOURCES += \
    main.cpp \
    object.cpp \
    worker.cpp \
    renderer.cpp \
    environment.cpp \
    world.cpp \
    assetmanager.cpp \
    filesystem.cpp \
    animator.cpp \
    background.cpp \
    units/unit.cpp \
    units/movable.cpp \
    units/camera.cpp \
    capabilities/capability.cpp \
    capabilities/controller.cpp \
    capabilities/player.cpp \
    capabilities/modulehandler.cpp \
    capabilities/modules/module.cpp \
    additional/spm.cpp \
    additional/timer.cpp \
    additional/event.cpp \
    additional/vector.cpp \
    additional/stringformer.cpp \
    loadable.cpp \
    audioplayer.cpp \
    capabilities/modules/weapon.cpp \
    units/projectile.cpp \
    context.cpp \
    capabilities/modules/engine.cpp \
    capabilities/modules/warpdrive.cpp \
    units/ship.cpp \
    gui/guielement.cpp \
    gui/guicontainer.cpp \
    gui/guilabel.cpp \
    gui/guibutton.cpp \
    iinformative.cpp \
    gui/guistack.cpp \
    capabilities/ai.cpp \
    units/station.cpp



HEADERS += \
    object.h \
    worker.h \
    renderer.h \
    environment.h \
    world.h \
    assetmanager.h \
    filesystem.h \
    animator.h \
    background.h \
    units/unit.h \
    units/movable.h \
    units/camera.h \
    capabilities/capability.h \
    capabilities/controller.h \
    capabilities/player.h \
    capabilities/modulehandler.h \
    capabilities/modules/module.h \
    additional/spm.h \
    additional/timer.h \
    additional/event.h \
    additional/vector.h \
    additional/stringformer.h \
    loadable.h \
    audioplayer.h \
    capabilities/modules/weapon.h \
    units/projectile.h \
    context.h \
    capabilities/modules/engine.h \
    capabilities/modules/warpdrive.h \
    units/ship.h \
    gui/guielement.h \
    gui/guicontainer.h \
    gui/guilabel.h \
    gui/guibutton.h \
    iinformative.h \
    gui/guistack.h \
    capabilities/ai.h \
    units/station.h





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
