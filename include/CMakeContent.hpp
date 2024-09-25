#ifndef __CMAKE_CONTENT
#define __CMAKE_CONTENT

#include "AbstractContent.hpp"
#include <string>
#include <inja.hpp>

struct CMakeContent: AbstractContent {
    
    const static std::string cmake_text ;
    
    virtual std::string file() const;
    virtual std::string template_text() const;
    virtual inja::json adapt(const inja::json &input) const;
};


#endif
