#ifndef CHARSET_H
#define CHARSET_H
#include "bitarray.h"
#include <cstring>
#include <string>


class charSet
{
private:
    const charSet* _refersTo;
    uint _refCount;
    bitArray* _arr;

    void _realloc();

public:
    charSet();
    charSet(const char* str);
    charSet(const std::string& str);
    charSet(const charSet &set);
    ~charSet();

    charSet& operator = (const charSet& ch);
    charSet& operator << (const char& ch);
    charSet& operator >> (const char& ch);
    charSet& operator -= (const charSet& set);
    charSet& operator ^= (const charSet& set);
    charSet& operator |= (const charSet& set);
    charSet& operator &= (const charSet& set);

    charSet operator + (const char& ch);
    charSet operator - (const char& ch);
    charSet operator - (const charSet& set);
    charSet operator ^ (const charSet& set);
    charSet operator | (const charSet& set);
    charSet operator & (const charSet& set);

    bool operator == (const charSet& set) const;
    bool operator != (const charSet& set) const;
    bool operator <= (const charSet& set) const;
    bool operator >= (const charSet& set) const;
    bool operator < (const charSet& set) const;
    bool operator > (const charSet& set) const;

    bool contains(const char& ch);
    friend std::ostream& operator << (std::ostream& stream, const charSet& set);
};

charSet make_charset(const char* str);
charSet make_charset(const std::string& str);


#endif // CHARSET_H
