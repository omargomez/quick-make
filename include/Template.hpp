#ifndef __TEMPLATE_HPP
#define __TEMPLATE_HPP

#include <string>
#include "inja.hpp"
#include "Input.hpp"
using namespace inja;

struct Template final {
    const std::string template_text;
    
    Template(const std::string &text) : template_text(text) {}
    
    std::string render(const Input &input) {
        return inja::render(template_text, input.data);
    }
};

#endif
