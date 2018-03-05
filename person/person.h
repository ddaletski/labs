#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <ctime>
#include <string>
#include <sstream>


typedef unsigned int uint;
class Person
{
protected:
    char* _name = 0;

public:
    Person(const char* name);
    Person() { _name = "John Doe"; }
    virtual ~Person() { if(_name) delete[] _name; }

    void set_name(const char* name);
    const char * const get_name() const { return _name; }

    virtual std::string to_string() const { return "Name: " + std::string(_name); }
    virtual void to_stream(std::ostream& str) const;

    friend std::ostream& operator << (std::ostream& stream, const Person& p);
};

#endif // PERSON_H
