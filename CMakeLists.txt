

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
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kmoduleswitch.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/ktype.h
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/kmetafunction.h

    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kcirclebuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kuniversalqueue.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/experimental/universalqueue/kvoidhandle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kabstractfactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kmoduleswitch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/memcontrol/kpull.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/kmetafunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/klibcore/src/utility/ktype.cpp
    )


target_include_directories(klibcore PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/klibcore>)



add_library(e172 SHARED
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/vector.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/math.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/textformat.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/abstractrenderengine.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/abstractrenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/image.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/math.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/vector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/abstractrenderengine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/abstractrenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/textformat.cpp
    )
target_include_directories(e172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/engine>)



add_executable(project172
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlgraphicsprovider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlrenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/world.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetmanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/filesystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/animator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/background.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/unit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/movable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capability.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modulehandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/module.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/rotozoom.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/spm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/time/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/event.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/stringformer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/effects/anaglyph.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/loadable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/weapon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/projectile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/context.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/warpdrive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/ship.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guielement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicontainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guistack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/ai.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/station.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/json/json_reader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/json/json_value.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/json/json_writer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/debug.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiswitch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/effects/visualeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guichoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/application.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/fpsmonitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/particle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/framebuilder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/socket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/state.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/trigger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/lightparticle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worldmanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/defaultworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/arenaworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/docker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guilist.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/aggressive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/heapworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/objectregistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/registryinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audiochannel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audiohardwarebank.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audioplayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/variant.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiminimap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiradar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/thruster.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/time/time.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimenuelement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/mutex.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/environment.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/object.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlgraphicsprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/src/sdlimplementation/sdlrenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worker.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/world.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetmanager.h
    ${CMAKE_CURRENT_LIST_DIR}/src/filesystem.h
    ${CMAKE_CURRENT_LIST_DIR}/src/animator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/background.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/unit.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/movable.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capability.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/controller.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/player.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modulehandler.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/module.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/rotozoom.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/spm.h
    ${CMAKE_CURRENT_LIST_DIR}/src/time/timer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/event.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/stringformer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/effects/anaglyph.h
    ${CMAKE_CURRENT_LIST_DIR}/src/loadable.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/weapon.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/projectile.h
    ${CMAKE_CURRENT_LIST_DIR}/src/context.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/engine.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/warpdrive.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/ship.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guielement.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicontainer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guistack.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/ai.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/station.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/writer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/allocator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/assertions.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/autolink.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/config.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/features.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/forwards.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/json.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/reader.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/value.h
    ${CMAKE_CURRENT_LIST_DIR}/src/json/version.h
    ${CMAKE_CURRENT_LIST_DIR}/src/debug.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiswitch.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/effects/visualeffect.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guichoice.h
    ${CMAKE_CURRENT_LIST_DIR}/src/application.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/fpsmonitor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/particle.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/framebuilder.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/net/socket.h
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src/state.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/trigger.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimain.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/lightparticle.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worldmanager.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/defaultworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/arenaworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/docker.h
    ${CMAKE_CURRENT_LIST_DIR}/src/near.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guilist.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/aggressive.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/heapworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/objectregistry.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/registryinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audio.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audiochannel.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audiohardwarebank.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/audioplayer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/variant.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiminimap.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiradar.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/modules/thruster.h
    ${CMAKE_CURRENT_LIST_DIR}/src/time/time.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimenuelement.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/mutex.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/environment.h
    )

target_include_directories(project172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_include_directories(project172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/klibcore>)
target_include_directories(project172 PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/engine>)


target_link_libraries(project172
    klibcore
    e172
    )
