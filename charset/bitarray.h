#ifndef BITARRAY_H
#define BITARRAY_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <exception>
#include <string>

class bitReference {
private:
    bitReference();
    char* _byte;
    size_t _offset;

    void make_one();
    void make_zero();


public:
    bitReference(char* const& byte, const size_t& offset);
    ~bitReference() {}

    bool operator == (const bitReference& ref) const;
    bool operator != (const bitReference& ref) const;
    bitReference& operator = (const bool& value);
    bitReference& operator = (const bitReference& ref);
    bitReference& operator += (const bitReference& ref);
    bitReference& operator -= (const bitReference& ref);
    bitReference& operator &= (const bitReference& ref);
    bitReference& operator |= (const bitReference& ref);
    bitReference& operator ^= (const bitReference& ref);

    bool operator + (const bitReference& ref) const;
    bool operator - (const bitReference& ref) const;
    bool operator & (const bitReference& ref) const;
    bool operator | (const bitReference& ref) const;
    bool operator ^ (const bitReference& ref) const;


    bool operator ~ () {return ~(*_byte & mask()); }

    char mask() const {
        // returns bit mask of byte, where this bit is 1 and others are 0
        return 255 & int(pow(2, _offset));
    }
    operator bool() const {return *_byte & mask();}

};

class OutOfBoundsException : std::exception {
    std::string _what_info;
public:
    OutOfBoundsException(const std::string& message = "index is out of bound") {
        _what_info = message;
    }

    const char* what() const throw() {
        return _what_info.c_str();
    }

};


class bitArray {
private:
    size_t _bit_size; // count of written bits
    size_t _byte_size; // count of written bytes (the last can be filled partically)
    char* _arr;

    void _clean();
    void _allocate(size_t bits);
    void _copy(const bitArray& arr);

public:
    bitArray();
    bitArray(const size_t& bits);
    bitArray(const bitArray& arr);
    ~bitArray() { delete[] _arr; }

    bitReference operator [](const size_t& pos);
    bitArray operator ~();
    bitArray& operator = (const bitArray& arr);
    bitReference at(const size_t& pos);

    size_t size() { return _bit_size; }
};

#endif // BITARRAY_H
