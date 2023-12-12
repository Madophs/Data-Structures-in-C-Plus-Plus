include_directories(${CMAKE_SOURCE_DIR}/trees/avl PRIVATE)

add_executable(avl_test avl_test.cc)

target_link_libraries(avl_test gtest_main gmock_main)

gtest_discover_tests(avl_test)
