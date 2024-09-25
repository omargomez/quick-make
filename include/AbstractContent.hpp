#ifndef __ABSTRACTCONTENT_HPP
#define __ABSTRACTCONTENT_HPP

#include <string>
#include <inja.hpp>

struct AbstractContent {
    virtual std::string file() const = 0;
    virtual std::string template_text() const = 0;
    virtual inja::json adapt(const inja::json &input) const {
        return input;
    }
};

#endif
