cmake_minimum_required(VERSION 3.28.3)
# Add test source files
set(TEST_SOURCES
    vec3_tests.cpp # Add more test files as needed
    color_tests.cpp
)

# Create the test executable
add_executable(ray_tracing_tests ${TEST_SOURCES})

# Link the ray_tracing_lib and Google Test to the test executable
target_link_libraries(ray_tracing_tests PRIVATE ray_tracing_lib GTest::gtest GTest::gtest_main)

# Add the include directory
target_include_directories(ray_tracing_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Register the tests with CTest
include(GoogleTest)
gtest_discover_tests(ray_tracing_tests)
