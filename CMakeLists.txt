

cmake_minimum_required(VERSION 3.0)
add_compile_options(-no-pie)
project(project172 DESCRIPTION "project172 game")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




add_library(klibcore SHARED
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kvoidhandle.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kcirclebuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kuniversalqueue.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kpull.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kabstractfactory.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/ktype.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/kmetafunction.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/ksmartenum.h

    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kcirclebuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kuniversalqueue.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kvoidhandle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kabstractfactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kpull.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/kmetafunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/ktype.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/ksmartenum.cpp
    )


target_include_directories(klibcore PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/klibcore>)

include(${CMAKE_CURRENT_LIST_DIR}/src/json/CMakeLists.txt)


add_library(e172 SHARED
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/assettools/abstractassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/assettools/abstractassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/assettools/assetprovider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/assettools/assetprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/assettools/loadable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/assettools/loadable.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/abstractaudioprovider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/abstractaudioprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/audiochannel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/audiochannel.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/audiosample.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/audiosample.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/graphics/abstractgraphicsprovider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/graphics/abstractgraphicsprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/graphics/abstractrenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/graphics/abstractrenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/graphics/image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/graphics/image.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/math.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/math.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/vector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/vector.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/memcontrol/abstractfactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/memcontrol/abstractfactory.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/memcontrol/abstractstrategy.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/memcontrol/abstractstrategy.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/time/deltatimecalculator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/time/deltatimecalculator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/time/elapsedtimer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/time/elapsedtimer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/time/time.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/time/time.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/abstracteventhandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/abstracteventhandler.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/additional.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/additional.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/context.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/context.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/entity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/entity.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/gameapplication.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/gameapplication.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/sharedcontainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/sharedcontainer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/textformat.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/textformat.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/type.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/type.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/variant.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/variant.h
    )
target_include_directories(e172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/engine>)

target_link_libraries(e172
    json
    )


add_library(sdl_impl
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/effects/anaglyph.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/effects/anaglyph.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/effects/visualeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/effects/visualeffect.h

    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/rotozoom.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/rotozoom.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlaudioprovider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlaudioprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdleventhandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdleventhandler.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlgraphicsprovider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlgraphicsprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlrenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlrenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/spm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/spm.h
    )

add_executable(project172
    ${CMAKE_CURRENT_LIST_DIR}/src/animator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/animator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/application.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/application.h
    ${CMAKE_CURRENT_LIST_DIR}/src/background.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/background.h
    ${CMAKE_CURRENT_LIST_DIR}/src/debug.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/debug.h
    ${CMAKE_CURRENT_LIST_DIR}/src/environment.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/environment.h
    ${CMAKE_CURRENT_LIST_DIR}/src/filesystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/filesystem.h
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.h
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.h
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src/object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/object.h
    ${CMAKE_CURRENT_LIST_DIR}/src/objectregistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/objectregistry.h
    ${CMAKE_CURRENT_LIST_DIR}/src/state.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/state.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worldmanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worldmanager.h

    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/fpsmonitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/fpsmonitor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/registryinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/registryinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.h

    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/framebuilder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/framebuilder.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/socket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/socket.h

    ${CMAKE_CURRENT_LIST_DIR}/src/additional/e_variant.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/e_variant.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/lightparticle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/lightparticle.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/mutex.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/mutex.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/speedindicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/speedindicator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/stringformer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/stringformer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/trigger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/trigger.h

    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/animatorassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/animatorassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/audioassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/audioassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/mapassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/mapassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/numberassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/numberassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/spriteassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/spriteassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/stringassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/stringassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/vectorassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/vectorassetexecutor.h

    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audioplayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audioplayer.h

    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/engine.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/module.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/module.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/thruster.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/thruster.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/warpdrive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/warpdrive.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/weapon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/weapon.h

    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/aggressive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/aggressive.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/ai.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/ai.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capability.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capability.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/controller.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/docker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/docker.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modulehandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modulehandler.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/player.h

    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guibaseelement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guibaseelement.h

    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guichoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guichoice.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicontainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicontainer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidebugvalueinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidebugvalueinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guielement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guielement.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guilist.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guilist.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimain.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimainshell.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimainshell.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimenuelement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimenuelement.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiminimap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiminimap.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiradar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiradar.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guistack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guistack.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiswitch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiswitch.h

    ${CMAKE_CURRENT_LIST_DIR}/src/units/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/movable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/movable.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/particle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/particle.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/projectile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/projectile.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/ship.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/ship.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/station.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/station.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/unit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/unit.h

    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/arenaworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/arenaworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/defaultworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/defaultworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/guisetup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/guisetup.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/heapworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/heapworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/world.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/world.h

    ${CMAKE_CURRENT_LIST_DIR}/src/animator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/animator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/application.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/application.h
    ${CMAKE_CURRENT_LIST_DIR}/src/background.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/background.h
    ${CMAKE_CURRENT_LIST_DIR}/src/debug.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/debug.h
    ${CMAKE_CURRENT_LIST_DIR}/src/environment.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/environment.h
    ${CMAKE_CURRENT_LIST_DIR}/src/filesystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/filesystem.h
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.h
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.h
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src/object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/object.h
    ${CMAKE_CURRENT_LIST_DIR}/src/objectregistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/objectregistry.h
    ${CMAKE_CURRENT_LIST_DIR}/src/state.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/state.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worldmanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worldmanager.h
    )

target_include_directories(project172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_include_directories(project172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/klibcore>)
target_include_directories(project172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/engine>)


target_link_libraries(project172
    klibcore
    e172
    json
    sdl_impl
    )
