# Brew dependencies inja, nlohmann
cmake_minimum_required(VERSION 3.28)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
project(Project)
include_directories(include)
add_executable(quick-cmake main.cpp)
target_include_directories(quick-cmake PRIVATE $ENV{HOMEBREW_REPOSITORY}/include)
install(TARGETS quick-cmake)
