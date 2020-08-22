

add_library(json SHARED
    ${CMAKE_CURRENT_LIST_DIR}/allocator.h
    ${CMAKE_CURRENT_LIST_DIR}/assertions.h
    ${CMAKE_CURRENT_LIST_DIR}/autolink.h
    ${CMAKE_CURRENT_LIST_DIR}/config.h
    ${CMAKE_CURRENT_LIST_DIR}/features.h
    ${CMAKE_CURRENT_LIST_DIR}/forwards.h
    ${CMAKE_CURRENT_LIST_DIR}/json.h
    ${CMAKE_CURRENT_LIST_DIR}/json_reader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_tool.h
    ${CMAKE_CURRENT_LIST_DIR}/json_value.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_writer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/reader.h
    ${CMAKE_CURRENT_LIST_DIR}/value.h
    ${CMAKE_CURRENT_LIST_DIR}/version.h
    ${CMAKE_CURRENT_LIST_DIR}/writer.h
    )
