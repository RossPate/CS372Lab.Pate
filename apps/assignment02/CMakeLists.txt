cmake_minimum_required(VERSION 3.8)

#set the project name
project(assignment02)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### Get the stuff we need to use Google Test...
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#add the test executable
add_executable(listtest listtest.cpp List.hpp)
target_link_libraries(listtest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(listtest)