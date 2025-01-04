cmake_minimum_required(VERSION 3.28.3)

project(ray_tracing)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define source files (add all your source files here)
set(SOURCES
    src/main.cpp
    src/vec3.cpp  # Add other source files as needed
)

# Define the include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create a static library for the core code
add_library(ray_tracing_lib STATIC ${SOURCES})

# Find TBB package (if needed)
find_package(TBB REQUIRED)

# Link TBB to the library
target_link_libraries(ray_tracing_lib PRIVATE TBB::tbb)

# Include Catch2 for testing
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0  # Replace with the desired version
)
FetchContent_MakeAvailable(Catch2)

# Add the test folder and link tests
add_subdirectory(tests)

# Create the main executable (ray_tracing)
add_executable(ray_tracing ${SOURCES})
target_link_libraries(ray_tracing PRIVATE ray_tracing_lib)  # Link the library here
