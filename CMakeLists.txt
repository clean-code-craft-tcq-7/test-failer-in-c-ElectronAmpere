cmake_minimum_required(VERSION 3.14)
project(StrongTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()


file(GLOB PROD_SOURCES "src/*.c")
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(strong_tests ${PROD_SOURCES} ${TEST_SOURCES})

# Copy expected_pairs.txt to build dir (fix for CI)
set(EXPECTED_PAIRS_SRC "${CMAKE_SOURCE_DIR}/test/expected_pairs.txt")
set(EXPECTED_PAIRS_DST "${CMAKE_BINARY_DIR}/expected_pairs.txt")
if (EXISTS ${EXPECTED_PAIRS_SRC})
  file(COPY ${EXPECTED_PAIRS_SRC} DESTINATION ${CMAKE_BINARY_DIR})
  message(STATUS "Copied expected_pairs.txt to build directory")
else()
  message(WARNING "expected_pairs.txt not found in ${CMAKE_SOURCE_DIR}/test/. Tests may fail. Commit the file to the repo.")
endif()

target_link_libraries(
  strong_tests
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(strong_tests)
