CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

PROJECT(Algorithms)

INCLUDE(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
INCLUDE(GoogleTest)
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/test,
    ${GTEST_INCLUDE_DIRS}/include
)

#ADD_SUBDIRECTORY(stack)
#ADD_SUBDIRECTORY(linked_list)
ADD_SUBDIRECTORY(trees)
ADD_SUBDIRECTORY(tests)

