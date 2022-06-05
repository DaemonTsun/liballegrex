
# tests
find_package(t1)

if (NOT DEFINED t1_DIR OR t1_DIR)
    add_test_directory("${CMAKE_CURRENT_LIST_DIR}")
    link_tests(${PROJECT_NAME})
    register_tests()
endif()
