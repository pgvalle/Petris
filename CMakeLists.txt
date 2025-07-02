cmake_minimum_required(VERSION 3.12)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include(FetchContent)
# FetchContent_Declare(SFML
#    GIT_REPOSITORY https://github.com/SFML/SFML.git
#   GIT_TAG 3.0.1
#   GIT_SHALLOW ON
#    EXCLUDE_FROM_ALL
#    SYSTEM)
# FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES src/*.cpp)

project(Petris)
add_executable(petris ${SOURCES})
# target_link_libraries(petris PRIVATE SFML::System SFML::Window SFML::Graphics)
target_link_libraries(petris PRIVATE sfml-system sfml-window sfml-graphics)