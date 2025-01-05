cmake_minimum_required(VERSION 3.28.3)

project(ray_tracing)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define source files (add all your source files here)
set(SOURCE src/main.cpp)

set(LIB_SRC
  src/vec3.cpp
)
# Define the include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create a static library for the core code
add_library(ray_tracing_lib STATIC ${LIB_SRC})

# Find TBB package (if needed)
find_package(TBB REQUIRED)

# Link TBB to the library
target_link_libraries(ray_tracing_lib PRIVATE TBB::tbb)

include(FetchContent)
FetchContent_Declare(
    GTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0  # Replace with the desired version
)
FetchContent_MakeAvailable(GTest)

# Enable testing with CTest
enable_testing()

# Add the test folder for test-related CMakeLists
add_subdirectory(tests)

# Create the main executable
add_executable(ray_tracing ${SOURCE})
target_link_libraries(ray_tracing PRIVATE ray_tracing_lib)  
