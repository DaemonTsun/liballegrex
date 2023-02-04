
# psp-module-format
set(psp_module_format_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")
find_sources(psp_module_format_SOURCES "${psp_module_format_SOURCES_DIR}")
find_headers(psp_module_format_HEADERS "${psp_module_format_SOURCES_DIR}")
add_executable(psp-module-format)
target_sources(psp-module-format PRIVATE ${psp_module_format_HEADERS} ${psp_module_format_SOURCES})
target_include_directories(psp-module-format PRIVATE "${CMAKE_SOURCE_DIR}" "${allegrex_SOURCES_DIR}" "${shl_SOURCES_DIR}" "${psp_module_format_SOURCES_DIR}")

# link
target_link_libraries(psp-module-format ${allegrex_TARGET})

# set_target_properties(psp-module-format PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
