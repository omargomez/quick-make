#ifndef __ABSTRACTCONTENT_HPP
#define __ABSTRACTCONTENT_HPP

#include <string>
#include "inja.hpp"
using namespace inja;

struct AbstractContent {
    virtual std::string file() const = 0;
    virtual std::string template_text() const = 0;
    virtual json adapt(const json &input) const {
        return input;
    }
};

#endif
