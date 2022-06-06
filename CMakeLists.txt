cmake_minimum_required(VERSION 3.18)

project(allegrex)

# sources
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp" "src/*.tcc")
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

# settings
set(CMAKE_CXX_STANDARD 17)

# libs
add_subdirectory(libkirk)

# includes
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR})

# target lib
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} kirk)

add_subdirectory(psp-elfdump)
add_subdirectory(tests)

# etc
add_subdirectory(psp-module-format)
