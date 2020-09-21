

cmake_minimum_required(VERSION 3.0)


add_library(project172_tests SHARED
    ${CMAKE_CURRENT_LIST_DIR}/waretest.h
    ${CMAKE_CURRENT_LIST_DIR}/waretest.cpp
    )


target_link_libraries(project172_tests
    e172
    )
