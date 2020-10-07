

cmake_minimum_required(VERSION 3.18)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(project172)

add_compile_options(-no-pie)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)








message("CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} " " ${CMAKE_CXX_COMPILER_VERSION})






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
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/audioplayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/audio/audioplayer.h


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
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/differentiator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/differentiator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/averagecalculator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/averagecalculator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/colider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/math/colider.h

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

    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/vectorproxy.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/vectorproxy.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/systeminfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/systeminfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/animator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/animator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/observer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/observer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/cycliciterator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/cycliciterator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/ptr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/utility/ptr.h

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
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/testprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/src/engine/testprovider.cpp
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



function(add_go_library TARGET_LIB GO_SRCS)
    set(GO_LIBNAME lib${TARGET_LIB}.so)
    message("TARGET_LIB: " ${TARGET_LIB})
    message("GO_LIBNAME: " ${GO_LIBNAME})
    message("GO_SRCS: " ${GO_SRCS})
    add_custom_command(OUTPUT ${GO_LIBNAME}
        DEPENDS ${GO_SRCS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND env go build -buildmode=c-shared -o "${CMAKE_CURRENT_BINARY_DIR}/${GO_LIBNAME}" ${CMAKE_GO_FLAGS} ${GO_SRCS}
        COMMENT "Building Go library"
        )

    add_custom_target(${TARGET_LIB}.lib DEPENDS ${GO_LIBNAME})
endfunction()

#add_library(go_test SHARED
#    ${CMAKE_CURRENT_LIST_DIR}/src/test.go
#    )


add_go_library(go_net
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/go/netservice.go
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/go/netclient.go
    )





add_executable(project172
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/experimental/injectableentity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/experimental/injectableentity.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/experimental/__capability.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/experimental/__capability.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/chartview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/chartview.h

    ${CMAKE_CURRENT_LIST_DIR}/src/appextensions/screensettingsextension.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/appextensions/screensettingsextension.h
    ${CMAKE_CURRENT_LIST_DIR}/src/appextensions/volumeobserverextension.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/appextensions/volumeobserverextension.h

    ${CMAKE_CURRENT_LIST_DIR}/src/background.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/background.h
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iinformative.h
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/near.h
    ${CMAKE_CURRENT_LIST_DIR}/src/worldpresetstrategy.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/worldpresetstrategy.h

    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/memstatearner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/memstatearner.h

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
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/segmentpaiter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/segmentpaiter.h

    ${CMAKE_CURRENT_LIST_DIR}/src/additional/ware/warecontainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/ware/warecontainer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/ware/waremultibaycontainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/ware/waremultibaycontainer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/ware/abstractwarecontainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/additional/ware/abstractwarecontainer.h


    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/animatorassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/animatorassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/audioassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/audioassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/spriteassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/spriteassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/vectorassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/vectorassetexecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/factoryassetexecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/factoryassetexecutor.h


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
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/warestorage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/warestorage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/factory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/factory.h

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
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiwareview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiwareview.h

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
    ${CMAKE_CURRENT_LIST_DIR}/src/testmodule.cppm
    )


include(${CMAKE_CURRENT_LIST_DIR}/src/vulkanimplementation/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/tests/CMakeLists.txt)

add_dependencies(project172 go_net.lib)

link_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(project172
    sdl_impl
    vulkan_impl
    e172
    project172_tests
    ${CMAKE_CURRENT_BINARY_DIR}/libgo_net.so
    #libgo_net
    )


if (UNIX)
    target_link_libraries(project172 dl X11 stdc++ stdc++fs)
endif (UNIX)

if (WIN32)
    target_link_libraries(project172 ws2_32)
endif (WIN32)

