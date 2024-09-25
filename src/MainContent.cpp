#include "MainContent.hpp"

std::string MainContent::file() const {
    return "main.cpp";
}

std::string MainContent::template_text() const {
    return main_text;
}

const std::string MainContent::main_text = R"(
#include <iostream>
{% if exists("sqlite") %}
#include <sqlite3.h>
{% endif %}
{% if exists("fltk") %}
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
{% endif %}

int main(int argc, char **argv) {

{% if exists("sqlite") %}
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open(":memory:", &DB);
{% endif %}

{% if exists("fltk") %}
    Fl_Window *window = new Fl_Window(300,180);
    Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
    box->box(FL_UP_BOX);
    box->labelsize(36);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);
    return Fl::run();
{% endif %}
})";

