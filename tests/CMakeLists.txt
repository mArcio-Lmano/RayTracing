# Add test source files (add all your test files here)
set(TEST_SOURCES
    vec3_tests.cpp  # Add other test files as needed
)

# Find the GTest package
find_package(GTest REQUIRED)

# Define the test executable
add_executable(vec3_tests ${TEST_SOURCES})

# Link Google Test and your ray_tracing library to the test executable
target_link_libraries(vec3_tests PRIVATE GTest::GTest GTest::Main ray_tracing_lib)

# Add the include directory for the source code
target_include_directories(vec3_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Ensure the test executable links against Catch2 or GTest, whichever you're using
