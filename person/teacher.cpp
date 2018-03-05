#include "teacher.h"
#include <cstring>

static char* copy_string(const char * const name) {
    char* str = new char[strlen(name) + 1];
    strcpy(str, name);
    return str;
}

Teacher::Teacher(const char* name, const char* department) : Person(name) {
    _department = copy_string(department);
}

std::string Teacher::to_string() const {
    std::ostringstream str;

    str << "Name: " << _name <<
            "\nDepartment: " << _department;

    return str.str();
}

void Teacher::set_department(const char* department) {
    _department = copy_string(department);
}
