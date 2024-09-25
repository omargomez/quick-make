#include <iostream>
#include <string>

#include <inja.hpp>
#include "Input.hpp"
#include "Output.hpp"
#include "Template.hpp"
#include "MainContent.hpp"
#include "CMakeContent.hpp"

using namespace inja;

class App final {
    const Input input;
    
public:
    App(Input const &_input) : input(_input) {}
    
    int run() {
        try {
            generate(MainContent());
            generate(CMakeContent());
            std::cout << "Done!\n";
            return EXIT_SUCCESS;
        } catch (const std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception thrown" << std::endl;
        }
        
        return EXIT_FAILURE;
    }
    
private:
    
    void generate(const AbstractContent &content) {
        auto text = ::Template(content.template_text()).render(content.adapt(input.data));
        Output(content.file()).write(text);
    }
    
};

int main(int argc, char *argv[]) {
    Input input = Input::parse_args(argc, argv);
    App app(input);
    return app.run();
}


