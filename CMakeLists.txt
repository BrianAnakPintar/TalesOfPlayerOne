cmake_minimum_required(VERSION 3.16)
project(TalesOfPlayerOne LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Collect all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

file(GLOB_RECURSE PROJECT_HEADERS "include/*.h" "include/*.hpp")

# Create the executable
add_executable(main ${SOURCES})
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/Resources")
add_compile_definitions(RESOURCES_DIR="${RESOURCES_DIR}")
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
