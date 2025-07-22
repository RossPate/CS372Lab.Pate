cmake_minimum_required(VERSION 3.11)

# Set the project name
project(Asg08_HashTableTest)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source
  ../../include
)

# Collect all source and header files
file(GLOB all_SRCS
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
  "${PROJECT_SOURCE_DIR}/*.cpp"
  "../../include/*.h"
  "../../include/*.hpp"
)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Windows compatibility
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(Asg08_HashTableTest ${all_SRCS})
target_link_libraries(Asg08_HashTableTest gtest_main)

# Enable Google Test discovery
include(GoogleTest)
gtest_discover_tests(Asg08_HashTableTest)