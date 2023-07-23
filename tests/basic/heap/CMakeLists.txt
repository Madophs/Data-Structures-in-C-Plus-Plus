INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/basic/heap PRIVATE)

add_executable(heap_test heap_test.cc)

target_link_libraries(heap_test gtest_main gmock_main)

gtest_discover_tests(heap_test)

