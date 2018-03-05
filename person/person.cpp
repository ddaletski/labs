#include "person.h"
#include <cstring>

static char* copy_string(const char * name) {
    char* str = new char[strlen(name) + 1];
    strcpy(str, name);
    return str;
}

Person::Person(const char* name) {
    _name = copy_string(name);
}

void Person::set_name(const char* name) {
    _name = copy_string(name);
}

void Person::to_stream(std::ostream& str) const {
    str << to_string();
}

std::ostream& operator <<(std::ostream &stream, const Person &p) {
    p.to_stream(stream);
    return stream;
}
