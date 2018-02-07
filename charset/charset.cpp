#include "charset.h"\

#define SET_SIZE 256


void charSet::_realloc() {
    if(_refersTo && _refersTo->_refCount == 0)
        _refersTo = NULL;

    if(_refCount || (_refersTo && _refersTo->_refCount)){
        bitArray* tmp = new bitArray(SET_SIZE);
        *tmp = *_arr;
        _arr = tmp;
        _refCount = 0;
        _refersTo = NULL;
        std::cout << "reallocation\n";
    }
}

charSet::charSet() {
    _arr = new bitArray(SET_SIZE);
    _refCount = 0;
    _refersTo = NULL;
}

charSet::charSet(const char *str) {
    _arr = new bitArray(SET_SIZE);
    _refCount = 0;
    _refersTo = NULL;
    for(uint i = 0; i < strlen(str); ++i)
        *this << str[i];
}

charSet::charSet(const std::string &str) : charSet(str.c_str()) {
}

charSet::charSet(const charSet &set) {
    _arr = set._arr;
    _refCount = 0;
    const_cast<charSet&>(set)._refCount++;
    _refersTo = &set;
}

charSet::~charSet() {
    if(_refCount == 0 && _refersTo == NULL)
        delete _arr;
    else if(_refersTo)
        const_cast<charSet*>(_refersTo)->_refCount--;
}

///////////////////////////////////////////////////////////


charSet &charSet::operator =(const charSet &set) {
    _arr = set._arr;
    const_cast<charSet&>(set)._refCount++;
    _refersTo = &set;
    return *this;
}

charSet &charSet::operator <<(const char &ch) {
    _realloc();
    (*_arr)[ch] = 1;
    return *this;
}

charSet &charSet::operator >>(const char &ch) {
    _realloc();
    (*_arr)[ch] = 0;
    return *this;
}

charSet &charSet::operator -=(const charSet &set) {
    _realloc();
    for(uint i = 0; i < SET_SIZE; ++i)
        if((*set._arr)[i])
            (*_arr)[i] = 0;
    return *this;
}

charSet &charSet::operator ^=(const charSet &set) {
    _realloc();
    for(uint i = 0; i < SET_SIZE; ++i)
        (*_arr)[i] ^= (*set._arr)[i];
    return *this;
}

charSet &charSet::operator |=(const charSet &set) {
    _realloc();
    for (uint i = 0; i < SET_SIZE; ++i)
        (*_arr)[i] |= (*set._arr)[i];
    return *this;
}

charSet &charSet::operator &=(const charSet &set) {
    _realloc();
    for(uint i = 0; i < SET_SIZE; ++i)
        (*_arr)[i] &= (*set._arr)[i];
    return *this;
}

/////////////////////////////////////////////////////

charSet charSet::operator +(const char &ch) {
    charSet temp = *this;
    temp << ch;
    return temp;
}

charSet charSet::operator -(const char &ch) {
    charSet temp = *this;
    temp >> ch;
    return temp;
}

charSet charSet::operator -(const charSet &set) {
    charSet temp = *this;
    temp -= set;
    return temp;
}

charSet charSet::operator ^(const charSet &set) {
    charSet temp = *this;
    temp ^= set;
    return temp;
}

charSet charSet::operator |(const charSet &set)
{
    charSet temp = *this;
    temp |= set;
    return temp;
}

charSet charSet::operator &(const charSet &set) {
    charSet temp = *this;
    temp &= set;
    return temp;
}

//////////////////////////////////////////////////////

bool charSet::operator ==(const charSet &set) const {
    for(uint i = 0; i < SET_SIZE; ++i)
        if((*_arr)[i] != (*set._arr)[i])
            return false;
    return true;
}

bool charSet::operator !=(const charSet &set) const {
    for(uint i = 0; i < SET_SIZE; ++i)
        if((*_arr)[i] != (*set._arr)[i])
            return true;
    return false;
}

bool charSet::operator <=(const charSet &set) const {
    for(uint i = 0; i < SET_SIZE; ++i)
        if((*_arr)[i] && !(*set._arr)[i])
            return false;
    return true;
}

bool charSet::operator >=(const charSet &set) const {
    for(uint i = 0; i < SET_SIZE; ++i)
        if((*set._arr)[i] && !(*_arr)[i])
            return false;
    return true;
}

bool charSet::operator <(const charSet &set) const {
    return (*this <= set && *this != set);
}

bool charSet::operator >(const charSet &set) const {
    return (*this >= set && *this != set);
}

bool charSet::contains(const char &ch) {
    return (*_arr)[ch];
}


/////////////////////////////////////////////////////

std::ostream& operator << (std::ostream &stream, const charSet& set) {
    for(uint i = 0; i < SET_SIZE; ++i)
        if((*set._arr)[i])
            stream << char(i) << "\n";
    return stream;
}

////////////////////////////////////////////////////////

charSet make_charset(const char* str) {
    charSet set;
    for(uint i = 0; i < strlen(str); ++i)
        set << str[i];
    return set;
}

charSet make_charset(const std::string& str) {
    charSet set;
    for(auto ch : str)
        set << ch;
    return set;
}

