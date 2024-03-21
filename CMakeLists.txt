cmake_minimum_required(VERSION 3.28.3)

project(ray_tracing)

# Add your source files here
set(SOURCES
    src/main.cpp
)

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Find TBB package
find_package(TBB REQUIRED)

# Link TBB to your executable
target_link_libraries(${PROJECT_NAME} PRIVATE TBB::tbb)

# Specify the C++ standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)  # Or the desired standard version
