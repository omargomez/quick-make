# Brew dependencies inja, nlohmann
cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
project(Project)
include_directories(include)

add_executable(quick-cmake src/main.cpp src/CMakeContent.cpp src/Template.cpp src/MainContent.cpp src/Input.cpp src/Output.cpp)
target_include_directories(quick-cmake PRIVATE external)
install(TARGETS quick-cmake)
