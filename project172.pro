
CONFIG += c++17


include(klibcore/klibcore.pri)

win32 {
#    INCLUDEPATH += C:\Qt\Tools\mingw730_64\include
    INCLUDEPATH += ./src
    INCLUDEPATH += C:\qt\5.15.0\mingw81_64\include
    LIBS += -LC:\qt\5.15.0\mingw81_64\lib -lws2_32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc
}

unix {
    QMAKE_CXXFLAGS += -rdynamic -O2
    INCLUDEPATH += ./src
    LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ldl
}



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/additional/informative/controllerfinder.h \
    src/additional/informative/fpsmonitor.h \
    src/additional/informative/registryinfo.h \
    src/additional/informative/unitsamountinfo.h \
    src/additional/lightparticle.h \
    src/additional/mutex.h \
    src/additional/net/framebuilder.h \
    src/additional/net/socket.h \
    src/additional/speedindicator.h \
    src/additional/stringformer.h \
    src/additional/trigger.h \
    src/additional/variant.cpp.new \
    src/additional/variant.h.new \
    src/animator.h \
    src/assetexecutors/animatorassetexecutor.h \
    src/assetexecutors/audioassetexecutor.h \
    src/assetexecutors/mapassetexecutor.h \
    src/assetexecutors/numberassetexecutor.h \
    src/assetexecutors/spriteassetexecutor.h \
    src/assetexecutors/stringassetexecutor.h \
    src/assetexecutors/vectorassetexecutor.h \
    src/audio/audioplayer.h \
    src/background.h \
    src/capabilities/aggressive.h \
    src/capabilities/ai.h \
    src/capabilities/capability.h \
    src/capabilities/controller.h \
    src/capabilities/docker.h \
    src/capabilities/modulehandler.h \
    src/capabilities/modules/engine.h \
    src/capabilities/modules/module.h \
    src/capabilities/modules/thruster.h \
    src/capabilities/modules/warpdrive.h \
    src/capabilities/modules/weapon.h \
    src/capabilities/player.h \
    src/debug.h \
    src/engine/abstracteventhandler.h \
    src/engine/functional/metafunction.h \
    src/engine/memcontrol/abstractfactory.h \
    src/engine/additional.h \
    src/engine/assettools/abstractassetexecutor.h \
    src/engine/assettools/assetprovider.h \
    src/engine/assettools/loadable.h \
    src/engine/audio/abstractaudioprovider.h \
    src/engine/audio/audiochannel.h \
    src/engine/audio/audiosample.h \
    src/engine/context.h \
    src/engine/entity.h \
    src/engine/gameapplication.h \
    src/engine/graphics/abstractgraphicsprovider.h \
    src/engine/graphics/abstractrenderer.h \
    src/engine/graphics/image.h \
    src/engine/math/math.h \
    src/engine/math/vector.h \
    src/engine/memcontrol/abstractstrategy.h \
    src/engine/messagequeue.h \
    src/engine/sfinae.h \
    src/engine/sharedcontainer.h \
    src/engine/textformat.h \
    src/engine/time/deltatimecalculator.h \
    src/engine/time/elapsedtimer.h \
    src/engine/time/time.h \
    src/engine/type.h \
    src/engine/typedefs.h \
    src/engine/variant.h \
    src/environment.h \
    src/filesystem.h \
    src/gui/base/guibaseelement.h \
    src/gui/base/guicontainer.h \
    src/gui/base/guielement.h \
    src/gui/base/guimenuelement.h \
    src/gui/base/guistack.h \
    src/gui/guiblushingfloatingmessage.h \
    src/gui/guicentralmessage.h \
    src/gui/guichoice.h \
    src/gui/guicombobox.h \
    src/gui/guidebugvalueinfo.h \
    src/gui/guifloatingmessage.h \
    src/gui/guilist.h \
    src/gui/guimain.h \
    src/gui/guiminimap.h \
    src/gui/guimoduleview.h \
    src/gui/guiradar.h \
    src/gui/guiswitch.h \
    src/iinformative.h \
    src/json/allocator.h \
    src/json/assertions.h \
    src/json/autolink.h \
    src/json/config.h \
    src/json/features.h \
    src/json/forwards.h \
    src/json/json.h \
    src/json/json_tool.h \
    src/json/json_valueiterator.inl \
    src/json/reader.h \
    src/json/value.h \
    src/json/version.h \
    src/json/writer.h \
    src/near.h \
    src/netlistener.h \
    src/object.h \
    src/objectregistry.h \
    src/openglimplementation/openglgraphicsprovider.h \
    src/openglimplementation/openglrenderer.h \
    src/sdlimplementation/effects/anaglyph.h \
    src/sdlimplementation/effects/visualeffect.h \
    src/sdlimplementation/rotozoom.h \
    src/sdlimplementation/sdlaudioprovider.h \
    src/sdlimplementation/sdleventhandler.h \
    src/sdlimplementation/sdlgraphicsprovider.h \
    src/sdlimplementation/sdlrenderer.h \
    src/sdlimplementation/spm.h \
    src/units/camera.h \
    src/units/movable.h \
    src/units/particle.h \
    src/units/projectile.h \
    src/units/ship.h \
    src/units/station.h \
    src/units/unit.h \
    src/worldmanager.h \
    src/worlds/arenaworld.h \
    src/worlds/defaultworld.h \
    src/worlds/guimaker.h \
    src/worlds/heapworld.h \
    src/worlds/world.h

SOURCES += \
    src/additional/informative/controllerfinder.cpp \
    src/additional/informative/fpsmonitor.cpp \
    src/additional/informative/registryinfo.cpp \
    src/additional/informative/unitsamountinfo.cpp \
    src/additional/lightparticle.cpp \
    src/additional/mutex.cpp \
    src/additional/net/framebuilder.cpp \
    src/additional/net/socket.cpp \
    src/additional/speedindicator.cpp \
    src/additional/stringformer.cpp \
    src/additional/trigger.cpp \
    src/animator.cpp \
    src/assetexecutors/animatorassetexecutor.cpp \
    src/assetexecutors/audioassetexecutor.cpp \
    src/assetexecutors/mapassetexecutor.cpp \
    src/assetexecutors/numberassetexecutor.cpp \
    src/assetexecutors/spriteassetexecutor.cpp \
    src/assetexecutors/stringassetexecutor.cpp \
    src/assetexecutors/vectorassetexecutor.cpp \
    src/audio/audioplayer.cpp \
    src/background.cpp \
    src/capabilities/aggressive.cpp \
    src/capabilities/ai.cpp \
    src/capabilities/capability.cpp \
    src/capabilities/controller.cpp \
    src/capabilities/docker.cpp \
    src/capabilities/modulehandler.cpp \
    src/capabilities/modules/engine.cpp \
    src/capabilities/modules/module.cpp \
    src/capabilities/modules/thruster.cpp \
    src/capabilities/modules/warpdrive.cpp \
    src/capabilities/modules/weapon.cpp \
    src/capabilities/player.cpp \
    src/debug.cpp \
    src/engine/abstracteventhandler.cpp \
    src/engine/functional/metafunction.cpp \
    src/engine/memcontrol/abstractfactory.cpp \
    src/engine/additional.cpp \
    src/engine/assettools/abstractassetexecutor.cpp \
    src/engine/assettools/assetprovider.cpp \
    src/engine/assettools/loadable.cpp \
    src/engine/audio/abstractaudioprovider.cpp \
    src/engine/audio/audiochannel.cpp \
    src/engine/audio/audiosample.cpp \
    src/engine/context.cpp \
    src/engine/entity.cpp \
    src/engine/gameapplication.cpp \
    src/engine/graphics/abstractgraphicsprovider.cpp \
    src/engine/graphics/abstractrenderer.cpp \
    src/engine/graphics/image.cpp \
    src/engine/math/math.cpp \
    src/engine/math/vector.cpp \
    src/engine/memcontrol/abstractstrategy.cpp \
    src/engine/messagequeue.cpp \
    src/engine/sharedcontainer.cpp \
    src/engine/textformat.cpp \
    src/engine/time/deltatimecalculator.cpp \
    src/engine/time/elapsedtimer.cpp \
    src/engine/time/time.cpp \
    src/engine/type.cpp \
    src/engine/variant.cpp \
    src/environment.cpp \
    src/filesystem.cpp \
    src/gui/base/guibaseelement.cpp \
    src/gui/base/guicontainer.cpp \
    src/gui/base/guielement.cpp \
    src/gui/base/guimenuelement.cpp \
    src/gui/base/guistack.cpp \
    src/gui/guiblushingfloatingmessage.cpp \
    src/gui/guicentralmessage.cpp \
    src/gui/guichoice.cpp \
    src/gui/guicombobox.cpp \
    src/gui/guidebugvalueinfo.cpp \
    src/gui/guifloatingmessage.cpp \
    src/gui/guilist.cpp \
    src/gui/guimain.cpp \
    src/gui/guiminimap.cpp \
    src/gui/guimoduleview.cpp \
    src/gui/guiradar.cpp \
    src/gui/guiswitch.cpp \
    src/iinformative.cpp \
    src/json/json_reader.cpp \
    src/json/json_value.cpp \
    src/json/json_writer.cpp \
    src/main.cpp \
    src/near.cpp \
    src/netlistener.cpp \
    src/object.cpp \
    src/objectregistry.cpp \
    src/openglimplementation/openglgraphicsprovider.cpp \
    src/openglimplementation/openglrenderer.cpp \
    src/sdlimplementation/effects/anaglyph.cpp \
    src/sdlimplementation/effects/visualeffect.cpp \
    src/sdlimplementation/rotozoom.cpp \
    src/sdlimplementation/sdlaudioprovider.cpp \
    src/sdlimplementation/sdleventhandler.cpp \
    src/sdlimplementation/sdlgraphicsprovider.cpp \
    src/sdlimplementation/sdlrenderer.cpp \
    src/sdlimplementation/spm.cpp \
    src/units/camera.cpp \
    src/units/movable.cpp \
    src/units/particle.cpp \
    src/units/projectile.cpp \
    src/units/ship.cpp \
    src/units/station.cpp \
    src/units/unit.cpp \
    src/worldmanager.cpp \
    src/worlds/arenaworld.cpp \
    src/worlds/defaultworld.cpp \
    src/worlds/guimaker.cpp \
    src/worlds/heapworld.cpp \
    src/worlds/world.cpp
