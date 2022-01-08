cmake_minimum_required(VERSION 3.18)

project(psp-elfdump)

# sources
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp" "src/*.tcc")
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

# settings
set(CMAKE_CXX_STANDARD 17)

# libs

# includes
include_directories(${CMAKE_SOURCE_DIR}/src)

# exe
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
add_custom_target(run COMMAND "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")

# link
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


