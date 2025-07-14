cmake_minimum_required(VERSION 3.11)

# Set the project name
project(Assignment05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
  ../../include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source
)

file(GLOB all_SRCS
  "../../include/*.h"
  "../../include/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
  "${PROJECT_SOURCE_DIR}/*.cpp"
)

# Get the stuff we need to use Google Test...
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add the executable
add_executable(treetest ${all_SRCS})
target_link_libraries(treetest gtest_main)

include(GoogleTest)
gtest_discover_tests(treetest)
