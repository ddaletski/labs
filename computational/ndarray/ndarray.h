#pragma once
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <memory>

typedef int Dim;
typedef std::vector<Dim> Index;
typedef Index Shape;
typedef Index TailSlice;


template <class DataType>
class NDArray {
private:
    Shape _shape;
    Shape _strides;
    std::shared_ptr<DataType[]> _data;

    bool checkInBounds(const Index& index) {
        for(int i = 0; i < index.size(); ++i) {
            if(index[i] >= _shape[i])
                return false;
        }
        return true;
    }

    void calculateStrides() {
        _strides.assign(_shape.begin(), _shape.end());
        _strides.push_back(1);

        for(int i = _strides.size() - 2; i >= 0; --i) {
            _strides[i] *= _strides[i+1];
        }
    }

    size_t indexToPos(const Index& index) const {
        size_t pos = 0;
        for(int i = 0; i < index.size(); ++i) {
            pos += index[i] * _strides[i+1];
        }
        return pos;
    }

    std::pair<size_t, size_t> tailSliceBounds(const TailSlice& sliceCoords) const {
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
            std::pair<size_t, size_t> bounds = tailSliceBounds(curr_slice);
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
    NDArray(const Index shape) : _shape(shape) {
        calculateStrides();
        size_t full_size = count();

        _data.reset(new DataType[full_size]);
    }

    NDArray(const Index shape, const DataType & value) : NDArray(shape) {
        size_t full_size = count();
        for(int i = 0; i < full_size; ++i) {
            _data[i] = value;
        }
    }

    ~NDArray() {
    }


    NDArray(const NDArray<DataType>& other) : _data(nullptr) {
        *this = other;
    }

    NDArray(NDArray<DataType>&& other) : _data(nullptr) {
        *this = std::move(other);
    }

    NDArray<DataType>& operator = (const NDArray<DataType>& other) {
        _shape = other._shape;
        calculateStrides();

        _data = other._data;

        return *this;
    }

    NDArray<DataType>& operator = (NDArray<DataType>&& other) {
        _shape = std::move(other._shape);
        _strides = std::move(other._strides);

        _data = other._data;

        return *this;
    }

    ////////////// getters ////////////////////

    size_t count() const {
        return _strides.front();
    }

    const Shape& shape() const {
        return _shape;
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

    /////////////////// shape and layout methods //////////////////////

    void reshape(const Shape & shape) {
        size_t newTotalSize = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<size_t>());
        if(count() != newTotalSize) {
            throw "incompatible shapes";
        }

        _shape = shape;
        calculateStrides();
    }

    NDArray<DataType> reshaped(const Shape & shape) {
        NDArray<DataType> copy = *this;
        copy.reshape(shape);
        return copy;
    }

    void transposed(const std::vector<size_t>& dims_permutation) {
        Shape trShape;
        Shape trStrides;

        // permute strides (starting from second) and shape according to permutation

        trStrides.push_back(_strides.front());
        for(auto dim : dims_permutation) {
            trStrides.push_back(_strides[dim+1]);
            trShape.push_back(_shape[dim]);
        }
        // indexToPos will point to data so as it's transposed

        // change shape to permuted

        // reshape data (mb per-element copy using indexToPos)
    }


    ///////////////////// reducers ////////////////////////

    const DataType& max(const Dim& dim) {
        if(dim < 0) {
            return *std::max_element(_data.get(), _data.get() + count(), std::less<DataType>());
        } else {
            return DataType();
        }
    }

    const DataType& min(const Dim& dim) {
        if(dim < 0) {
            return *std::min_element(_data.get(), _data.get() + count(), std::less<DataType>());
        } else {
            return DataType();
        }
    }

    ///////////////////////////////////////////////////////

    friend std::ostream& operator << (std::ostream& stream, const NDArray & array) {
        stream << "[";
        array.outputOneDimension(stream, {});
        stream << "]";
        return stream;
    }
};
