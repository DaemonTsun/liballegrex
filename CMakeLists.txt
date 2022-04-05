cmake_minimum_required(VERSION 3.18)

project(allegrex)

# sources
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp" "src/*.tcc")
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

# settings
set(CMAKE_CXX_STANDARD 17)

# libs

# includes
include_directories(${CMAKE_SOURCE_DIR}/src)

# target lib
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

# psp-elfdump
file(GLOB_RECURSE ELFDUMP_HEADERS "psp-elfdump/*.h" "psp-elfdump/*.hpp" "psp-elfdump/*.tcc")
file(GLOB_RECURSE ELFDUMP_SOURCES "psp-elfdump/*.c" "psp-elfdump/*.cpp")
add_executable(psp-elfdump ${HEADERS} ${ELFDUMP_HEADERS} ${ELFDUMP_SOURCES})

# link
target_link_libraries(psp-elfdump ${PROJECT_NAME})


