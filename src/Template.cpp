#include "Template.hpp"
#include "Input.hpp"

std::string Template::render(const Input &input) {
    return inja::render(template_text, input.data);
}

std::string Template::render(const inja::json &data) {
    return inja::render(template_text, data);
}

