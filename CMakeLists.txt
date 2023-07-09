cmake_minimum_required(VERSION 3.16)

project(project172 VERSION 0.0.5)

if(NOT (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
  add_compile_options(-no-pie)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath='${ORIGIN}'")

set(DEPENDENCIES_PREFIX "${CMAKE_BINARY_DIR}/dep_prefix")

include(${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172/cmake/utils.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172)

set(ENABLE_FIND_E172_PACKAGE
    OFF
    CACHE BOOL "Disable find package for e172 impls")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172_sdl_impl)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172_vulkan_impl)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172_console_impl)

e172_install_public_headers(e172 ${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172/src
                            ${DEPENDENCIES_PREFIX}/include/e172)
e172_install_public_headers(
  e172_sdl_impl ${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172_sdl_impl/src
  ${DEPENDENCIES_PREFIX}/include/e172/impl/sdl)
e172_install_public_headers(
  e172_vulkan_impl ${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172_vulkan_impl/src
  ${DEPENDENCIES_PREFIX}/include/e172/impl/vulkan)
e172_install_public_headers(
  e172_console_impl ${CMAKE_CURRENT_LIST_DIR}/3rdparty/e172_console_impl/src
  ${DEPENDENCIES_PREFIX}/include/e172/impl/console)

configure_file(${CMAKE_CURRENT_LIST_DIR}/project.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/generated/config/project.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)

add_library(
  project172_core SHARED
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
  ${CMAKE_CURRENT_LIST_DIR}/src/informative.h
  ${CMAKE_CURRENT_LIST_DIR}/src/near.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/near.h
  ${CMAKE_CURRENT_LIST_DIR}/src/worldpresetstrategy.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/worldpresetstrategy.h
  ${CMAKE_CURRENT_LIST_DIR}/src/messagetype.h
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/controllerfinder.h
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/informative/unitsamountinfo.h
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/memstatearner.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/memstatearner.h
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/taskconsole.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/taskconsole.h
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
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/pricetable.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/additional/pricetable.h
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
  ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/templatevectorassetexecutor.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/templatevectorassetexecutor.h
  ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/nodesassetexecutor.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/nodesassetexecutor.h
  ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/assetexecutors.h
  ${CMAKE_CURRENT_LIST_DIR}/src/assetexecutors/assetexecutors.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capabilitysynchronizer.h
  ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capabilitysynchronizer.cpp
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
  ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capabilities.h
  ${CMAKE_CURRENT_LIST_DIR}/src/capabilities/capabilities.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/task.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/task.h
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/dockingtask.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/dockingtask.h
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/buywaretask.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/buywaretask.h
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/sellwaretask.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/sellwaretask.h
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/tradetask.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/tradetask.h
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/tasks.h
  ${CMAKE_CURRENT_LIST_DIR}/src/tasks/tasks.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guielement.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guielement.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guimenu.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guimenu.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guimenuelement.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guimenuelement.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guistack.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guistack.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guifocusswitch.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guifocusswitch.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guicontainer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guicontainer.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guisingleelementlistview.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/base/guisingleelementlistview.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiblushingfloatingmessage.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guicentralmessage.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidebugvalueinfo.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guidebugvalueinfo.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessage.h
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessagecontainer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guifloatingmessagecontainer.h
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
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiconsole.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/gui/guiconsole.h
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
  ${CMAKE_CURRENT_LIST_DIR}/src/units/units.h
  ${CMAKE_CURRENT_LIST_DIR}/src/units/units.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/persons/person.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/persons/person.h
  ${CMAKE_CURRENT_LIST_DIR}/src/persons/faction.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/persons/faction.h
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
  ${CMAKE_CURRENT_LIST_DIR}/src/packagetype.h)

# include(${CMAKE_CURRENT_LIST_DIR}/sdl_implementation/sdl_implementation.cmake)
# include(${CMAKE_CURRENT_LIST_DIR}/vulkan_implementation/vulkan_implementation.cmake)
# include(${CMAKE_CURRENT_LIST_DIR}/console_impl/console_impl.cmake)

file(GLOB_RECURSE ASSETS_SRC "${CMAKE_CURRENT_LIST_DIR}/assets/*")
add_custom_target(assets ALL SOURCES ${ASSETS_SRC})
e172_copy_target(assets ${CMAKE_CURRENT_BINARY_DIR})

# add_dependencies(project172_core E172) add_dependencies(sdl_impl E172)
# add_dependencies(vulkan_impl E172) add_dependencies(console_impl E172)

target_link_libraries(project172_core e172)

if(UNIX)
  target_link_libraries(project172_core dl X11 stdc++ stdc++fs)
endif(UNIX)

if(WIN32)
  target_link_libraries(project172_core ws2_32)
endif(WIN32)

add_executable(
  project172
  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/renderlayer.h
  ${CMAKE_CURRENT_LIST_DIR}/src/renderlayer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/flags.h
  ${CMAKE_CURRENT_LIST_DIR}/src/flags.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/debugchart.h
  ${CMAKE_CURRENT_LIST_DIR}/src/debugchart.cpp)

target_link_libraries(project172 e172 e172_sdl_impl e172_vulkan_impl
                      e172_console_impl project172_core)

add_executable(
  project172_tests
  ${CMAKE_CURRENT_LIST_DIR}/tests/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests/warecontainerspec.h
  ${CMAKE_CURRENT_LIST_DIR}/tests/warecontainerspec.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests/personspec.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests/personspec.h)

target_link_libraries(project172_tests e172 project172_core)

target_include_directories(project172_core
                           PRIVATE ${DEPENDENCIES_PREFIX}/include)
target_link_directories(project172_core PRIVATE ${DEPENDENCIES_PREFIX}/lib)

target_include_directories(e172_sdl_impl PRIVATE ${DEPENDENCIES_PREFIX}/include)
target_link_directories(e172_sdl_impl PRIVATE ${DEPENDENCIES_PREFIX}/lib)

target_include_directories(e172_vulkan_impl
                           PRIVATE ${DEPENDENCIES_PREFIX}/include)
target_link_directories(e172_vulkan_impl PRIVATE ${DEPENDENCIES_PREFIX}/lib)

target_include_directories(e172_console_impl
                           PRIVATE ${DEPENDENCIES_PREFIX}/include)
target_link_directories(e172_console_impl PRIVATE ${DEPENDENCIES_PREFIX}/lib)

target_include_directories(project172 PRIVATE ${DEPENDENCIES_PREFIX}/include)
target_link_directories(project172 PRIVATE ${DEPENDENCIES_PREFIX}/lib)

target_include_directories(project172_tests
                           PRIVATE ${DEPENDENCIES_PREFIX}/include)
target_link_directories(project172_tests PRIVATE ${DEPENDENCIES_PREFIX}/lib)

target_include_directories(console_video_player
                           PRIVATE ${DEPENDENCIES_PREFIX}/include)
target_link_directories(console_video_player PRIVATE ${DEPENDENCIES_PREFIX}/lib)

enable_testing()
include(CTest)
e172_target_discover_tests(project172_tests)
