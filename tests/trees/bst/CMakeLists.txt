INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/trees/bst PRIVATE)

add_executable(bst_test bst_test.cc)

target_link_libraries(bst_test gtest_main gmock_main)

gtest_discover_tests(bst_test)
