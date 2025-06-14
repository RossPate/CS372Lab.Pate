# CMakeList.txt : CMake project for assignment03, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("assignment03")
enable_testing()
# Add source to this project's executable.
add_executable (assignment03 "testCircularList.cpp" "circularList.h" "List.h" "Bag.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET assignment03 PROPERTY CXX_STANDARD 20)
endif()

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
include_directories(${CMAKE_SOURCE_DIR}/build/_deps/googletest-src/googletest/include/)
#add the test executable
add_executable(testCircularList testCircularList.cpp circularList.h)
target_link_libraries(testCircularList gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(testCircularList)