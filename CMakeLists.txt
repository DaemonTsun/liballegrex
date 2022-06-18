cmake_minimum_required(VERSION 3.18)

project(allegrex)

# sources
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

# settings
set(CMAKE_CXX_STANDARD 17)

# libs
add_subdirectory(libkirk)

# target lib
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} kirk)

# includes
target_include_directories(allegrex PUBLIC ./)
target_include_directories(allegrex PUBLIC ./src)

add_subdirectory(psp-elfdump)
add_subdirectory(tests)

# etc
add_subdirectory(psp-module-format)
