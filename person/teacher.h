#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"

class Teacher : public Person {
protected:
    char* _department;

public:
    Teacher(const char* name, const char* department);
    virtual ~Teacher() {if(_department) delete[] _department;}

    std::string to_string() const;

    void set_department(const char* department);

    const char * const get_department() { return _department; }
};

#endif // TEACHER_H
