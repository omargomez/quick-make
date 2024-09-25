#ifndef __OUTPUT
#define __OUTPUT

#include <string>
#include <fstream>
#include <iostream>

struct Output final {
    
    const std::string file;
    std::ofstream out;
    
    Output(const std::string &someFile) : file(someFile) {}
    
    void write(const std::string &string);
};

#endif
