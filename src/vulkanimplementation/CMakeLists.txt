cmake_minimum_required(VERSION 3.0)


add_library(vulkan_impl SHARED
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/graphicsobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/graphicsobject.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/graphicsobjectcreateinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/graphicsobjectcreateinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/hardware.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/hardware.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/extensiontools.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/extensiontools.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/validation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/validation.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/stringvector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/stringvector.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/presentationobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/presentationobject.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/vulkaninstancefactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/vulkaninstancefactory.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/logicdevicefactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/logicdevicefactory.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/swapchain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/swapchain.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/renderpass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/renderpass.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/commandpool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/graphicsobject/commandpool.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertex.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertex.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/externaltexvertexobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/externaltexvertexobject.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/descriptorsetlayout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/descriptorsetlayout.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/mesh.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/tools/mesh.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/pipeline.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/pipeline.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/font.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/font.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/abstractvertexobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/abstractvertexobject.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/bootstrapobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/bootstrapobject.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/texturedvertexobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/texturedvertexobject.h
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/wirevertexobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/e172vp/vertexobjects/wirevertexobject.h



    ${CMAKE_CURRENT_LIST_DIR}/vulkanrenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/vulkanrenderer.cpp

    ${CMAKE_CURRENT_LIST_DIR}/vulkangraphicsprovider.h
    ${CMAKE_CURRENT_LIST_DIR}/vulkangraphicsprovider.cpp

)


find_package(Vulkan REQUIRED)
#find_package(glfw3 REQUIRED)

target_link_libraries(vulkan_impl PRIVATE
    Vulkan::Vulkan
    SDL2
    freetype
    e172
    )

target_include_directories(vulkan_impl PRIVATE $<BUILD_INTERFACE:/usr/include/freetype2>)
