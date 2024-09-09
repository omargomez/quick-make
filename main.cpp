#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <stdio.h>
#include <string>

#include "Input.hpp"
#include "Template.hpp"
#include "AbstractContent.hpp"

// Inja
// ⚠️  TODO: Install single include inja, and let's make it local to the project
// #include <inja/inja.hpp>
#include "inja.hpp"
using namespace inja;

struct MainContent: AbstractContent {
    
    const static std::string main_text;
    
    virtual std::string file() const {
        return "main.cpp";
    }

    virtual std::string template_text() const {
        return main_text;
    }

};

const std::string MainContent::main_text = R"(
#include <iostream>
{% if exists("sqlite") %}
#include <sqlite3.h>
{% endif %}
{% if exists("fltk") %}
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
{% endif %}

int main(int argc, char **argv) {

{% if exists("sqlite") %}
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open(":memory:", &DB);
{% endif %}

{% if exists("fltk") %}
    Fl_Window *window = new Fl_Window(300,180);
    Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
    box->box(FL_UP_BOX);
    box->labelsize(36);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);
    return Fl::run();
{% endif %}
})";

struct CMakeContent: AbstractContent {
    
    const static std::string cmake_text ;
    
    virtual std::string file() const {
        return "CMakeLists.txt";
    }

    virtual std::string template_text() const {
        return cmake_text;
    }

    virtual json adapt(const json &input) const {
        json data {input};

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
};

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

struct Output final {
    
    const std::string file;
    std::ofstream out;
    
    Output(const std::string &someFile) : file(someFile) {}
    
    void write(const std::string &string) {
        out.open(file);
        if (out.fail()) {
            throw std::runtime_error("Write error!");
        }
        out << string;
        out.flush();
        if (out.bad()) {
            throw std::runtime_error("Write error!");
        }
        out.close();
    }
};

class App final {
    const Input input;
    
private:
public:
    App(Input const &_input) : input(_input) {}
    
    int run() {
        try {
            MainContent main{};
            CMakeContent cmake{};
            Output(main.file()).write(::Template(main.template_text()).render(main.adapt(input.data)));
            Output(cmake.file()).write(::Template(cmake.template_text()).render(cmake.adapt(input.data)));
//            Output("CMakeLists.txt").write(::Template(cmake_text).render(input));
            std::cout << "Done!\n";
            return EXIT_SUCCESS;
        } catch (const std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception thrown" << std::endl;
        }
        
        return EXIT_FAILURE;
    }
};

int main(int argc, char *argv[]) {
    Input input = Input::parse_args(argc, argv);
    App app(input);
    return app.run();
}


