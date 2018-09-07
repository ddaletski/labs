#pragma once
#include <vector>
#include <numeric>
#include <functional>
#include <iostream>

typedef size_t Dim;
typedef std::vector<Dim> Index;
typedef Index Shape;
typedef Index TailSlice;


template <class DataType>
class NDArray {
private:
    Shape _shape;
    Shape _shapeCumProd;
    DataType* _data;

    bool checkInBounds(const Index& index) {
        for(int i = 0; i < index.size(); ++i) {
            if(index[i] >= _shape[i])
                return false;
        }
        return true;
    }

    void calculateShapeProd() {
        _shapeCumProd.assign(_shape.begin(), _shape.end());
        _shapeCumProd.push_back(1);

        for(int i = _shapeCumProd.size() - 2; i >= 0; --i) {
            _shapeCumProd[i] *= _shapeCumProd[i+1];
        }
    }

    size_t indexToPos(const Index& index) const {
        size_t pos = 0;
        for(int i = 0; i < index.size(); ++i) {
            pos += index[i] * _shapeCumProd[i+1];
        }
        return pos;
    }

    std::pair<size_t, size_t> sliceBounds(const TailSlice& sliceCoords) const {
        auto index = sliceCoords;

        index.push_back(0);
        size_t begin = indexToPos(index);

        index.back() = _shape.back();
        size_t end = indexToPos(index);

        return {begin, end};
    }

    void outputOneDimension(std::ostream & ss, const TailSlice& curr_slice) const {
        size_t curr_dim = curr_slice.size();

        if(curr_dim == _shape.size() - 1) {
            std::pair<size_t, size_t> bounds = sliceBounds(curr_slice);
            for(int i = bounds.first; i < bounds.second; ++i) {
                ss << _data[i];
                if(i < bounds.second-1) {
                    ss << " ";
                }
            }
        } else {
            auto new_slice = curr_slice;
            new_slice.push_back(0);

            for(int i = 0; i < _shape[curr_dim]; ++i) {
                ss << "[";
                new_slice.back() = i;
                outputOneDimension(ss, new_slice);
                ss << "]";
            }
        }
    }

public:
    NDArray(const Index shape, const DataType & value)
        : _shape(shape)
    {
        calculateShapeProd();
        size_t full_size = count();

        _data = new DataType[full_size];
        for(int i = 0; i < full_size; ++i) {
            _data[i] = value;
        }
    }

    ~NDArray() {
        delete[] _data;
    }

    size_t count() const {
        return _shapeCumProd.front();
    }

    const DataType& operator() (const Index & index) const {
        if(index.size() != _shape.size()) {
            throw "incompatible index dimentionality";
        }
        if(!checkInBounds(index)) {
            throw "out of bounds";
        }
        return _data[indexToPos(index)];
    }

    DataType& operator() (const Index & index) {
        if(index.size() != _shape.size()) {
            throw "incompatible index dimentionality";
        }
        if(!checkInBounds(index)) {
            throw "out of bounds";
        }
        return _data[indexToPos(index)];
    }

    friend std::ostream& operator << (std::ostream& stream, const NDArray & array) {
        stream << "[";
        array.outputOneDimension(stream, {});
        stream << "]";
        return stream;
    }
};
