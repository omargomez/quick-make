#ifndef __INPUT_HPP
#define __INPUT_HPP

#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <stdio.h>
#include <string>
#include "inja.hpp"
//using namespace inja;

struct Input final {
public:
    const inja::json data;
    
    Input(const inja::json &some_data) : data(some_data) {}
    
    static Input parse_args(int argc, char *argv[]);
private:
    
    static bool validate(int argc, char *argv[]);
};

#endif
