#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <stdio.h>
#include <string>

// Inja
// ⚠️ TODO: Install single include inja, and let's make it local to the project
#include <inja/inja.hpp>
using namespace inja;

struct Input final {
public:
    const json data;
    
    Input(json some_data) : data(some_data) {}
    
    static Input parse_args(int argc, char *argv[]) {
        const char *use = "Use: quick-cmake [+sqlite] [+fltk] <project_name>\n";
        if (!Input::validate(argc, argv)) {
            std::cout << use;
            exit(1);
        }
        
        json data;
        
        // Store params
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '+') {
                data[argv[i] + 1] = argv[i];
            } else {
                data["target"] = argv[i];
            }
        }
        
        Input result(data);
        return result;
    }
    
private:
    
    static bool validate(int argc, char *argv[]) {
        if (argc < 2) {
            return false;
        }

        for (int i = 1; i < argc; i++) {
            auto current = argv[i];
            auto currentLen = strlen(current);
            if (currentLen == 0) {
                return false;
            }
            
            if (current[0] == '+' && currentLen <= 2) {
                return false;
            }
            
            if (current[0] == '+') {
                if (i == argc - 1) {
                    return false;
                }
                if (strcmp(current + 1, "sqlite") && strcmp(current + 1, "fltk")) {
                    return false;
                }
            } else {
                if (i != argc - 1) {
                    return false;
                }
            }
        }
        return true;
    }
    
};

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

struct Template final {
    const std::string template_text;
    
    Template(const std::string &text) : template_text(text) {}
    
    std::string render(const Input &input) {
        return inja::render(template_text, input.data);
    }
};

class App final {
    const Input input;
    
private:
    const std::string main_text = R"(
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char **argv) {
{% if exists("sqlite") %} // sqlite !{% endif %}
  Fl_Window *window = new Fl_Window(300,180);
  Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
  box->box(FL_UP_BOX);
  box->labelsize(36);
  box->labelfont(FL_BOLD+FL_ITALIC);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);
  return Fl::run();
})";
    
    const std::string cmake_text = R"(
cmake_minimum_required(VERSION 3.15)
project(Project)
# Uncomment to set custom package path
# list(APPEND CMAKE_PREFIX_PATH "/Users/omar.gomez1/.local")
find_package(FLTK CONFIG REQUIRED)
add_executable({{ target }} WIN32 MACOSX_BUNDLE main.cpp)
target_link_libraries({{ target }}  PRIVATE fltk::fltk)
)";
    
public:
    App(Input const &_input) : input(_input) {}
    
    int run() {
        try {
            Output("main.cpp").write(::Template(main_text).render(input));
            Output("CMakeLists.txt").write(::Template(cmake_text).render(input));
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
