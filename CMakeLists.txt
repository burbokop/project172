

cmake_minimum_required(VERSION 3.0)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(project172)

add_compile_options(-no-pie)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})

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
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/kinematics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/kinematics.h



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
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/physicalobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/physicalobject.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/smartenum.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/smartenum.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/object.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/objectregistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/objectregistry.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/messagequeue.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/messagequeue.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/functional/metafunction.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/functional/metafunction.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/debug.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/debug.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/sfinae.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/typedefs.h

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/args.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/args.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/matrix.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/matrix.cpp
    )

include(${CMAKE_CURRENT_LIST_DIR}/src/json/CMakeLists.txt)
target_link_libraries(e172
    json
    )


add_library(sdl_impl SHARED

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

target_link_libraries(sdl_impl
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    e172
    )


add_executable(project172
    ${CMAKE_CURRENT_LIST_DIR}/src/appextensions/screensettingsextension.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/appextensions/screensettingsextension.h
    ${CMAKE_CURRENT_LIST_DIR}/src/animator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/animator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/background.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/background.h
    ${CMAKE_CURRENT_LIST_DIR}/src/old_debug.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/old_debug.h
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.h
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.h
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/netlistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worldpresetstrategy.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worldpresetstrategy.h

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

    ${CMAKE_CURRENT_LIST_DIR}/src/additional/lightparticle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/lightparticle.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/speedindicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/speedindicator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/stringformer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/stringformer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/trigger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/trigger.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/docking/physicaldockingattractor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/docking/physicaldockingattractor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/docking/dockingnodepool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/docking/dockingnodepool.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/docking/dockingsession.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/docking/dockingsession.h

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
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guielement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guielement.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guicontainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guicontainer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guimenuelement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guimenuelement.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guistack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guistack.h

    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guichoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guichoice.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidebugvalueinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidebugvalueinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimain.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiminimap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiminimap.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiradar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiradar.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiswitch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiswitch.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimoduleview.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guimoduleview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicombobox.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicombobox.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guilistview.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guilistview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guistringlistview.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guistringlistview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guibutton.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guibutton.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidockingview.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidockingview.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/units/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/projectile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/projectile.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/ship.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/ship.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/station.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/station.h
    ${CMAKE_CURRENT_LIST_DIR}/src/units/unit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/units/unit.h
    ${CMAKE_CURRENT_LIST_DIR}/src/injectableentity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/injectableentity.h

    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/arenaworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/arenaworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/defaultworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/defaultworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/guimaker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/guimaker.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/heapworld.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/heapworld.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/world.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worlds/world.h

    ${CMAKE_CURRENT_LIST_DIR}/src/explosivespawner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/explosivespawner.h
    ${CMAKE_CURRENT_LIST_DIR}/src/ftestobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ftestobject.h
    )


include(${CMAKE_CURRENT_LIST_DIR}/src/vulkanimplementation/CMakeLists.txt)


target_link_libraries(project172
    sdl_impl
    vulkan_impl
    e172
    )


if (UNIX)
    target_link_libraries(project172 dl X11 stdc++ stdc++fs)
endif (UNIX)

if (WIN32)
    target_link_libraries(project172 ws2_32)
endif (WIN32)

