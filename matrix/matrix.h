#ifndef MATRIX_H
#define MATRIX_H
#
#include <cstdlib>
#include <initializer_list>
#include <functional>
#include <iomanip>
#include <iostream>

typedef unsigned int uint;

class OutOfBoundsException : public std::exception {
    std::string _what_info;
public:
    OutOfBoundsException(const std::string& message = "index is out of bounds") {
        _what_info = message;
    }
    virtual ~OutOfBoundsException() {}

    const char* what() const noexcept { return _what_info.c_str(); }
};


class WrongDimensionException : public std::exception {
    std::string _what_info;
public:
    WrongDimensionException(const std::string& message = "inappropriate dimension") {
        _what_info = message;
    }
    ~WrongDimensionException() { }

    const char* what() const noexcept { return _what_info.c_str(); }
};


class ZeroDivisionException : std::exception {
    std::string what_info = "zero division exception occured\n";
public:
    const char* what() const noexcept { return what_info.c_str(); }
};


template <class T>
class matrix
{
private:
    static uint count_of_instances;
    static uint max_count_of_instances;

    uint ID;
    uint _rows;
    uint _cols;
    T** _data;

    ///////////////////////////////////////////////

    void _fill(const T& value) {
        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < _cols; ++j)
                _data[i][j] = value;
    }

    void _fill(const std::function<T(uint, uint)>& func) {
        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < _cols; ++j)
                _data[i][j] = func(i, j);
    }

    void _copy(const matrix& m) {
        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < _cols; ++j)
                _data[i][j] = m._data[i][j];
    }

    void _erase() {
        for(uint i = 0; i < _rows; ++i)
            delete[] _data[i];
        delete[] _data;
    }

    void _allocate() {
        _data = new T*[_rows];
        for(uint i = 0; i < _rows; ++i)
            _data[i] = new T[_cols];
    }

    void _apply(const std::function<void(T&)>& func) {
        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < _cols; ++j)
                func(_data[i][j]);

    }

    ///////////////////////////////////////////////////

public:
    matrix(uint rows, uint cols, const T& value = T()) {
        ID = ++max_count_of_instances;
        count_of_instances++;
        _rows = rows;
        _cols = cols;
        _allocate();
        _fill(value);
    }

    matrix(uint rows, uint cols, const std::function<T(uint, uint)>& func) {
        ID = ++max_count_of_instances;
        count_of_instances++;
        _rows = rows;
        _cols = cols;
        _allocate();
        _fill(func);
    }

    explicit matrix(const matrix& m) {
        ID = ++max_count_of_instances;
        count_of_instances++;
        _rows = m._rows;
        _cols = m._cols;
        _allocate();
        _copy(m);
    }

    ~matrix() {
        _erase();
        count_of_instances--;
    }

    const uint& getID() { return ID; }
    static const uint& get_count_of_instances() { return count_of_instances; }

    ///////////////////////////////////////////////////
    void fill(const std::function<T(uint, uint)>& func) {
        _fill(func);
    }

    void fill(const T& value) {
        _fill(value);
    }

    void apply(const std::function<void(T&)>& func) {
        _apply(func);
    }
    /////////////////////////////////////////////////

    T* operator [] (uint row) noexcept {
        return _data[row];
    }

    T& operator [] (std::initializer_list<int> list) noexcept {
        return _data[*list.begin()][*list.begin()+1];
    }

    T& at(uint row, uint col) {
        if(row > _rows)
            throw OutOfBoundsException("row index is out of bounds");
        if(col > _cols)
            throw OutOfBoundsException("column index is out of bounds");
        return _data[row][col];
    }

    ///////////////////////////////////////////////////

    friend std::ostream& operator << (std::ostream& stream, const matrix<T>& m) {
        for(uint i = 0; i < m._rows; ++i) {
            for(uint j = 0; j < m._cols; ++j)
                stream << std::setw(3) << m._data[i][j] << " ";
            stream << "\n";
        }
        return stream;
    }

    void print(std::ostream& stream) {
        stream << *this << std::endl;
    }

    //////////////////////////////////////////////////////

    friend std::istream& operator >> (std::istream& stream, matrix<T>& m) {
        for(uint i = 0; i < m._rows; ++i)
            for(uint j = 0; j < m._cols; ++j)
                stream >> m._data[i][j];
        return stream;
    }

    void fill_console() {
        std::cout << "filling matrix with " << \
                     _rows << " rows and " << \
                     _cols << " columns\n";
        for(uint i = 0; i < _rows; ++i) {
            std::cout << "[" << i << "] row: ";
            for(uint j = 0; j < _cols; ++j)
                std::cin >> _data[i][j];
        }
    }

    /////////////////////////////////////////////////////

    matrix& operator = (const matrix& m) {
        if(_rows != m._rows || _cols != m._cols)
            _erase();
        _rows = m._rows;
        _cols = m._cols;
        _allocate();
        _copy(m);
        return *this;
    }

    matrix& operator *= (const T& scalar) {
        _apply([&](T& val) {val *= scalar;});
        return *this;
    }

    matrix& operator /= (const T& scalar) {
        if(scalar == 0)
            throw ZeroDivisionException();
        _apply([&](T& val) {val /= scalar;});
        return *this;
    }

    matrix& operator += (const matrix& m) {
        if(_rows != m._rows || _cols != m._cols)
            throw WrongDimensionException(\
                    "+ defined only for matrices with the same size");

        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < _cols; ++j)
                _data[i][j] += m._data[i][j];
        return *this;
    }

    matrix& operator -= (const matrix& m) {
        if(_rows != m._rows || _cols != m._cols)
            throw WrongDimensionException(\
                    "- defined only for matrices with the same size");

        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < _cols; ++j)
                _data[i][j] -= m._data[i][j];
        return *this;
    }
    ////////////////////////////////////////////////////////

    matrix operator + (const matrix& m){
        matrix temp = *this;
        temp += m;
        return temp;
    }

    matrix operator - (const matrix& m){
        matrix temp = *this;
        temp -= m;
        return temp;
    }

    matrix operator * (const T& scalar) {
        matrix temp = *this;
        temp *= scalar;
        return temp;
    }

    matrix operator / (const T& scalar) {
        matrix temp = *this;
        temp /= scalar;
        return temp;
    }

    matrix operator -() {
        matrix temp = *this;
        temp._apply([](T& elem) { elem = -elem; });
        return temp;
    }

    friend matrix operator * (const T& scalar, const matrix& m) {
        matrix temp = m;
        temp *= scalar;
        return temp;
    }
    //////////////////////////////////////////////////////////////

    matrix dot(const matrix& m) {
        if(_cols != m._rows)
            throw WrongDimensionException("dot product requires M1.cols == M2.rows");

        matrix product(_rows, m._cols);
        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < m._cols; ++j)
                for(uint k = 0; k < _cols; ++k)
                    product[i][j] += _data[i][k] * m._data[k][j];

        return product;
    }

    matrix operator * (const matrix& m) {
        return this->dot(m);
    }

    /////////////////////////////////////////////////////////////

    bool operator == (const matrix& m) const {
        if(_rows != m._rows || _cols != m._cols)
            return false;
        for(uint i = 0; i < _rows; ++i)
            for(uint j = 0; j < _cols; ++j)
                if(_data[i][j] != m._data[i][j])
                    return false;
        return true;
    }

    bool operator != (const matrix& m) const {
        return !(*this == m);
    }

    ////////////////////////////////////////////////////////////
};

template <class T>
uint matrix<T>::count_of_instances = 0;

template <class T>
uint matrix<T>::max_count_of_instances = 0;

#endif // MATRIX_H
