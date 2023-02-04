
# psp-elfdump
set(psp_elfdump_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")
find_sources(psp_elfdump_SOURCES "${psp_elfdump_SOURCES_DIR}")
find_headers(psp_elfdump_HEADERS "${psp_elfdump_SOURCES_DIR}")
add_executable(psp-elfdump)
target_sources(psp-elfdump PRIVATE ${psp_elfdump_HEADERS} ${psp_elfdump_SOURCES})
target_include_directories(psp-elfdump PRIVATE ${CMAKE_SOURCE_DIR} ${allegrex_SOURCES_DIR} ${shl_SOURCES_DIR})

# link
target_link_libraries(psp-elfdump ${allegrex_TARGET})

# set_target_properties(psp-elfdump PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
