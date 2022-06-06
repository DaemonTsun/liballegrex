
# psp-elfdump
file(GLOB_RECURSE ELFDUMP_HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE ELFDUMP_SOURCES "*.c" "*.cpp")
add_executable(psp-elfdump ${HEADERS} ${ELFDUMP_HEADERS} ${ELFDUMP_SOURCES})

# link
target_link_libraries(psp-elfdump ${PROJECT_NAME} kirk)

# i fucking hate cmake so much
# set_target_properties(psp-elfdump PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
