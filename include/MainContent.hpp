#ifndef __MAIN_CONTENT
#define __MAIN_CONTENT

#include "AbstractContent.hpp"
#include <string>

struct MainContent: AbstractContent {
    
    const static std::string main_text;
    
    virtual std::string file() const;
    virtual std::string template_text() const;

};

#endif
