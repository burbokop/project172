QT -= gui core

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -rdynamic -O2

win32 {
    INCLUDEPATH += C:\Qt\Tools\mingw730_64\include
    LIBS += -lws2_32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc
}

unix {
    INCLUDEPATH += ./src
    LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ldl
}


SOURCES += \
    src/main.cpp \
    src/object.cpp \
    src/worker.cpp \
    src/renderer.cpp \
    src/environment.cpp \
    src/worlds/world.cpp \
    src/assetmanager.cpp \
    src/filesystem.cpp \
    src/animator.cpp \
    src/background.cpp \
    src/units/unit.cpp \
    src/units/movable.cpp \
    src/units/camera.cpp \
    src/capabilities/capability.cpp \
    src/capabilities/controller.cpp \
    src/capabilities/player.cpp \
    src/capabilities/modulehandler.cpp \
    src/capabilities/modules/module.cpp \
    src/additional/rotozoom.cpp \
    src/additional/spm.cpp \
    src/additional/timer.cpp \
    src/additional/event.cpp \
    src/additional/vector.cpp \
    src/additional/stringformer.cpp \
    src/additional/effects/anaglyph.cpp \
    src/loadable.cpp \
    src/capabilities/modules/weapon.cpp \
    src/units/projectile.cpp \
    src/context.cpp \
    src/capabilities/modules/engine.cpp \
    src/capabilities/modules/warpdrive.cpp \
    src/units/ship.cpp \
    src/gui/guielement.cpp \
    src/gui/guicontainer.cpp \
    src/gui/guilabel.cpp \
    src/gui/guibutton.cpp \
    src/iinformative.cpp \
    src/gui/guistack.cpp \
    src/capabilities/ai.cpp \
    src/units/station.cpp \
    src/json/json_reader.cpp \
    src/json/json_value.cpp \
    src/json/json_writer.cpp \
    src/debug.cpp \
    src/gui/guiswitch.cpp \
    src/additional/effects/visualeffect.cpp \
    src/gui/guichoice.cpp \
    src/application.cpp \
    src/additional/informative/fpsmonitor.cpp \
    src/units/particle.cpp \
    src/additional/net/framebuilder.cpp \
    src/additional/net/socket.cpp \
    src/netlistener.cpp \
    src/state.cpp \
    src/additional/trigger.cpp \
    src/gui/guimain.cpp \
    src/gui/guicentralmessage.cpp \
    src/additional/informative/controllerfinder.cpp \
    src/gui/guifloatingmessage.cpp \
    src/gui/guiblushingfloatingmessage.cpp \
    src/additional/math.cpp \
    src/additional/lightparticle.cpp \
    src/worldmanager.cpp \
    src/worlds/defaultworld.cpp \
    src/worlds/arenaworld.cpp \
    src/additional/auto.cpp \
    src/capabilities/docker.cpp \
    src/near.cpp \
    src/gui/guilist.cpp \
    src/capabilities/aggressive.cpp \
    src/worlds/heapworld.cpp \
    src/objectregistry.cpp \
    src/additional/informative/registryinfo.cpp \
    src/audio/audio.cpp \
    src/audio/audiochannel.cpp \
    src/audio/audiohardwarebank.cpp \
    src/audio/audioplayer.cpp


HEADERS += \
    src/object.h \
    src/worker.h \
    src/renderer.h \
    src/environment.h \
    src/worlds/world.h \
    src/assetmanager.h \
    src/filesystem.h \
    src/animator.h \
    src/background.h \
    src/units/unit.h \
    src/units/movable.h \
    src/units/camera.h \
    src/capabilities/capability.h \
    src/capabilities/controller.h \
    src/capabilities/player.h \
    src/capabilities/modulehandler.h \
    src/capabilities/modules/module.h \
    src/additional/rotozoom.h \
    src/additional/spm.h \
    src/additional/timer.h \
    src/additional/event.h \
    src/additional/vector.h \
    src/additional/stringformer.h \
    src/additional/effects/anaglyph.h \
    src/loadable.h \
    src/capabilities/modules/weapon.h \
    src/units/projectile.h \
    src/context.h \
    src/capabilities/modules/engine.h \
    src/capabilities/modules/warpdrive.h \
    src/units/ship.h \
    src/gui/guielement.h \
    src/gui/guicontainer.h \
    src/gui/guilabel.h \
    src/gui/guibutton.h \
    src/iinformative.h \
    src/gui/guistack.h \
    src/capabilities/ai.h \
    src/units/station.h \
    src/json/writer.h \
    src/json/allocator.h \
    src/json/assertions.h \
    src/json/autolink.h \
    src/json/config.h \
    src/json/features.h \
    src/json/forwards.h \
    src/json/json.h \
    src/json/reader.h \
    src/json/value.h \
    src/json/version.h \
    src/json_tool.h \
    src/json_valueiterator.inl \
    src/debug.h \
    src/gui/guiswitch.h \
    src/additional/effects/visualeffect.h \
    src/gui/guichoice.h \
    src/application.h \
    src/additional/informative/fpsmonitor.h \
    src/units/particle.h \
    src/additional/net/framebuilder.h \
    src/additional/net/socket.h \
    src/netlistener.h \
    src/state.h \
    src/additional/trigger.h \
    src/gui/guimain.h \
    src/gui/guicentralmessage.h \
    src/additional/informative/controllerfinder.h \
    src/gui/guifloatingmessage.h \
    src/gui/guiblushingfloatingmessage.h \
    src/additional/math.h \
    src/additional/lightparticle.h \
    src/worldmanager.h \
    src/worlds/defaultworld.h \
    src/worlds/arenaworld.h \
    src/additional/auto.h \
    src/capabilities/docker.h \
    src/near.h \
    src/gui/guilist.h \
    src/capabilities/aggressive.h \
    src/worlds/heapworld.h \
    src/objectregistry.h \
    src/additional/informative/registryinfo.h \
    src/audio/audio.h \
    src/audio/audiochannel.h \
    src/audio/audiohardwarebank.h \
    src/audio/audioplayer.h




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
