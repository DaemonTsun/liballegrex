cmake_minimum_required(VERSION 3.18)
find_package(better REQUIRED NO_DEFAULT_PATH PATHS ext/better-cmake/cmake)

project(allegrex VERSION 1.0.0)
project_author("DaemonTsun")
get_version_target(allegrex_TARGET ${PROJECT_NAME})

if(TARGET ${allegrex_TARGET})
    return()
endif()

# settings
set(CMAKE_CXX_STANDARD 17)

# sources
set(allegrex_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
generate_project_header("${allegrex_SOURCES_DIR}/${PROJECT_NAME}/lib${PROJECT_NAME}_info.hpp")
find_sources(allegrex_SOURCES "${allegrex_SOURCES_DIR}")
find_headers(allegrex_HEADERS "${allegrex_SOURCES_DIR}")

# libs
add_subdirectory(libkirk)
add_subdirectory(ext/shl)

# target lib
add_library(${allegrex_TARGET} SHARED)
target_sources(${allegrex_TARGET} PUBLIC ${allegrex_SOURCES} ${allegrex_HEADERS})
target_include_directories(${allegrex_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}" "${allegrex_SOURCES_DIR}" "${shl_SOURCES_DIR}")
set_property(TARGET ${allegrex_TARGET} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${allegrex_TARGET} PRIVATE ${shl_TARGET} kirk)

if (NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    export_library_variables(allegrex)
    return()
endif()


add_subdirectory(psp-elfdump)

# etc
add_subdirectory(tests)
add_subdirectory(psp-module-format)
