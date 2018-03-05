#include "student.h"

Student::Student(const char* name,
                 uint grade,
                 uint group) :
    Person(name)
{
    _grade = grade;
    _group = group;
}

std::string Student::to_string() const {
    std::ostringstream str;
    str << "Name: " << _name <<
           "\nGrade: " << _grade <<
           "\nGroup: " << _group;

    return str.str();
}
