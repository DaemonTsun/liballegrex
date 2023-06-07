cmake_minimum_required(VERSION 3.18)
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ext/better-cmake/cmake/betterConfig.cmake")
    execute_process(COMMAND git submodule update --init "${CMAKE_CURRENT_SOURCE_DIR}/ext/better-cmake" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}") 
endif()
find_package(better REQUIRED NO_DEFAULT_PATH PATHS ext/better-cmake/cmake)

project(liballegrex)
project_author("DaemonTsun")

add_subdirectory(libkirk)

set(TEST_SOURCE_DIR ${ROOT}/tests)

add_lib(allegrex STATIC
    VERSION 1.0.2
    SOURCES_DIR "${ROOT}/src/"
    INCLUDE_DIRS "${ROOT}"
    GENERATE_TARGET_HEADER "${ROOT}/src/allegrex/liballegrex.hpp"
    CPP_VERSION 20
    CPP_WARNINGS ALL SANE FATAL
    LIBRARIES kirk
    EXT
        LIB shl 0.7.0 "${ROOT}/ext/shl" INCLUDE LINK GIT_SUBMODULE
    TESTS "${TEST_SOURCE_DIR}"
    )

set(shl_SOURCES_DIR "${shl-0.7_SOURCES_DIR}")

exit_if_included()

add_subdirectory(psp-elfdump)
add_subdirectory(psp-module-format)
