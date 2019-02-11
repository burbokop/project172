<<<<<<< HEAD
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS


win32 {
    INCLUDEPATH += C:\Qt\Tools\mingw730_64\include
    LIBS += -lws2_32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc
}

unix {
    LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
}

SOURCES += \
    main.cpp \
    object.cpp \
    worker.cpp \
    renderer.cpp \
    environment.cpp \
    worlds/world.cpp \
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
    additional/rotozoom.cpp \
    additional/spm.cpp \
    additional/timer.cpp \
    additional/event.cpp \
    additional/vector.cpp \
    additional/stringformer.cpp \
    additional/effects/anaglyph.cpp \
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
    units/station.cpp \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_writer.cpp \
    debug.cpp \
    gui/guiswitch.cpp \
    additional/effects/visualeffect.cpp \
    gui/guichoice.cpp \
    application.cpp \
    additional/fpsmonitor.cpp \
    units/particle.cpp \
    additional/net/framebuilder.cpp \
    additional/net/socket.cpp \
    netlistener.cpp \
    state.cpp \
    additional/trigger.cpp \
    gui/guimain.cpp \
    gui/guicentralmessage.cpp \
    additional/controllerfinder.cpp \
    gui/guifloatingmessage.cpp \
    gui/guiblushingfloatingmessage.cpp \
    additional/math.cpp \
    additional/lightparticle.cpp \
    worldmanager.cpp \
    worlds/defaultworld.cpp \
    worlds/arenaworld.cpp \
    additional/auto.cpp



HEADERS += \
    object.h \
    worker.h \
    renderer.h \
    environment.h \
    worlds/world.h \
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
    additional/rotozoom.h \
    additional/spm.h \
    additional/timer.h \
    additional/event.h \
    additional/vector.h \
    additional/stringformer.h \
    additional/effects/anaglyph.h \
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
    units/station.h \
    json/writer.h \
    json/allocator.h \
    json/assertions.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/reader.h \
    json/value.h \
    json/version.h \
    json_tool.h \
    json_valueiterator.inl \
    debug.h \
    gui/guiswitch.h \
    additional/effects/visualeffect.h \
    gui/guichoice.h \
    application.h \
    additional/fpsmonitor.h \
    units/particle.h \
    additional/net/framebuilder.h \
    additional/net/socket.h \
    netlistener.h \
    state.h \
    additional/trigger.h \
    gui/guimain.h \
    gui/guicentralmessage.h \
    additional/controllerfinder.h \
    gui/guifloatingmessage.h \
    gui/guiblushingfloatingmessage.h \
    additional/math.h \
    additional/lightparticle.h \
    worldmanager.h \
    worlds/defaultworld.h \
    worlds/arenaworld.h \
    additional/auto.h






# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
=======
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -ljsoncpp \
        -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

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
    additional/rotozoom.cpp \
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
    additional/rotozoom.h \
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
>>>>>>> bb28ef4c91e43a9b6eb286493020c8bd8b79425f
