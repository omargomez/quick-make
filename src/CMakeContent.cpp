#include "CMakeContent.hpp"


std::string CMakeContent::file() const {
    return "CMakeLists.txt";
}

std::string CMakeContent::template_text() const {
    return cmake_text;
}

inja::json CMakeContent::adapt(const inja::json &input) const {
    
    auto data = input;

    std::string libs {""};

    if (data.contains("fltk")) {
      data["EXE"] = "WIN32 MACOSX_BUNDLE";
      libs.append("fltk::fltk");
    }

    if (data.contains("sqlite")) {
      if (libs.length() > 0) {
        libs.append(" ");
      }
      libs.append("SQLite::SQLite3");
    }

    data["LIBS"] = libs;

    return data;
}

const std::string CMakeContent::cmake_text = R"(
cmake_minimum_required(VERSION 3.15)
project(Project)
# Uncomment to set custom package path
# list(APPEND CMAKE_PREFIX_PATH "/Users/omar.gomez1/.local")
{% if exists("sqlite") %}find_package(SQLite3 REQUIRED) {% endif %}
{% if exists("fltk") %}find_package(FLTK CONFIG REQUIRED) {% endif %}
add_executable({{ target }} {{ default(EXE, "") }} main.cpp)
target_link_libraries({{ target }} PRIVATE {{ default(LIBS, "") }})
)";

