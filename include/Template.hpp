#ifndef __TEMPLATE_HPP
#define __TEMPLATE_HPP

#include <string>
#include <inja.hpp>

class Input;

struct Template final {
    const std::string template_text;
    
    Template(const std::string &text) : template_text(text) {}
    
    std::string render(const Input &input);
    std::string render(const inja::json &data);
};

#endif
