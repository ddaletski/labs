#include "bitarray.h"

void bitReference::make_one()
{
    *_byte |= mask();
}

void bitReference::make_zero()
{
    *_byte &= ~mask();
}

bitReference::bitReference(char* const& byte, const size_t& offset) {
    /* byte is byte, containing this bit
         * offset is offset from the 1 bit of this byte */
    _byte = byte;
    _offset = offset;
}

bool bitReference::operator ==(const bitReference &ref) const
{
    return bool(*this) == bool(ref);
}

bool bitReference::operator !=(const bitReference &ref) const
{
    return bool(*this) != bool(ref);
}


bitReference& bitReference::operator = (const bool& value) {
    if(value)
        make_one();
    else
        make_zero();
    return *this;
}


bitReference& bitReference::operator = (const bitReference& ref) {
    if(this == &ref)
        return *this;
    if(ref)
        make_one();
    else
        make_zero();
    return *this;
}

bitReference &bitReference::operator +=(const bitReference &ref)
{
    if(ref == *this)
        make_zero();
    else
        make_one();
    return *this;
}

bitReference &bitReference::operator -=(const bitReference &ref)
{
    if(ref == *this)
        make_zero();
    else
        make_one();
    return *this;
}

bitReference &bitReference::operator &=(const bitReference &ref)
{
    if(!ref)
        make_zero();
    return *this;
}

bitReference &bitReference::operator |=(const bitReference &ref)
{
    if(ref)
        make_one();
    return *this;
}

bitReference &bitReference::operator ^=(const bitReference &ref)
{
    if(ref == *this)
        make_zero();
    else
        make_one();
    return *this;
}

bool bitReference::operator +(const bitReference &ref) const
{
    return (ref == *this) ? 1 : 0;
}

bool bitReference::operator -(const bitReference &ref) const
{
    return (ref == *this) ? 1 : 0;
}

bool bitReference::operator &(const bitReference &ref) const
{
    return (~ref || ~*this) ? 0 : 1;
}

bool bitReference::operator |(const bitReference &ref) const
{
    return ref ? 1 : bool(*this);
}

bool bitReference::operator ^(const bitReference &ref) const
{
    return (ref == *this) ? 0 : 1;
}


//////////////////////////////////////////////////////////////////////////

void bitArray::_clean() {
    delete[] _arr;
    _bit_size = _byte_size = 0;
}


void bitArray::_allocate(size_t bits) {
    _bit_size = bits;
    _byte_size = (_bit_size - 1) / 8 + 1;

    _arr = new char[_byte_size];
    for(size_t i = 0; i < _byte_size; ++i)
        _arr[i] = 0;
}


void bitArray::_copy(const bitArray &arr) {
    for(size_t i = 0; i < arr._byte_size; ++i)
        _arr[i] = arr._arr[i];
}

////////////////////////////////////////////////////////////////////////

bitArray::bitArray(const size_t& bits) {
    _allocate(bits);
}


bitArray::bitArray(const bitArray &arr)
{
    _allocate(arr._bit_size);
    _copy(arr);
}

/////////////////////////////////////////////////////////////////////////

bitReference bitArray::operator [](const size_t& pos) {
    size_t bytePos = pos / 8;
    size_t offset = pos % 8;
    return bitReference(_arr + bytePos, offset);
}


bitArray bitArray::operator ~() {
    bitArray temp(_bit_size);
    for(size_t i = 0; i < _bit_size; ++i)
        temp[i] = ~temp[i];
    return temp;
}


bitArray &bitArray::operator =(const bitArray &arr) {
    if(_bit_size)
        _clean();
    _allocate(arr._bit_size);
    _copy(arr);
    return *this;
}

bitReference bitArray::at(const size_t &pos)
{
    if(pos >= _bit_size)
        throw OutOfBoundsException();
    return operator [](pos);
}
