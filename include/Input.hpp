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
using namespace inja;

struct Input final {
public:
    const json data;
    
    Input(const json &some_data) : data(some_data) {}
    
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

#endif
