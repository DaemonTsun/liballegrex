
# tests
find_package(t1)

if (NOT DEFINED t1_DIR OR t1_DIR)
    add_test_directory("${CMAKE_CURRENT_LIST_DIR}"
                       INCLUDE_DIRS "${CMAKE_SOURCE_DIR}" "${allegrex_SOURCES_DIR}" "${shl_SOURCES_DIR}"
                       LIBRARIES "${allegrex_TARGET}")
    register_tests()
endif()
