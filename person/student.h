#ifndef STUDENT_H
#define STUDENT_H
#include "person.h"

class Student : public Person {
protected:
    uint _grade;
    uint _group;

public:
    Student(const char* name, uint grade=1, uint group=1);
    virtual ~Student() {}

    std::string to_string() const;

    void set_grade(uint grade) { _grade = grade; }
    void set_group(uint group) { _group = group; }

    uint get_grade() { return _grade; }
    uint get_group() { return _group; }
};

#endif // STUDENT_H
