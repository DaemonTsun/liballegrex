
# psp-elfdump
file(GLOB_RECURSE ELFDUMP_HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE ELFDUMP_SOURCES "*.c" "*.cpp")
add_executable(psp-elfdump ${HEADERS} ${ELFDUMP_HEADERS} ${ELFDUMP_SOURCES})

# link
target_link_libraries(psp-elfdump ${PROJECT_NAME} kirk)
