# Brew dependencies inja, nlohmann
cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
project(Project)
add_executable(quick-cmake main.cpp)
target_include_directories(quick-cmake PRIVATE external)
install(TARGETS quick-cmake)
