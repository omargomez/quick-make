#include "Output.hpp"

void Output::write(const std::string &string) {
    out.open(file);
    if (out.fail()) {
        throw std::runtime_error("Write error!");
    }
    out << string;
    out.flush();
    if (out.bad()) {
        throw std::runtime_error("Write error!");
    }
    out.close();
}
