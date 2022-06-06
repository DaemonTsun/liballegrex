
# psp-module-format
file(GLOB_RECURSE MODULE_FORMAT_HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE MODULE_FORMAT_SOURCES "*.c" "*.cpp")
add_executable(psp-module-format ${HEADERS} ${MODULE_FORMAT_HEADERS} ${MODULE_FORMAT_SOURCES})

# link
target_link_libraries(psp-module-format ${PROJECT_NAME} kirk)

# set_target_properties(psp-module-format PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
