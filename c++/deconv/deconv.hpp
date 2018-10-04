#ifndef DECONV
#define DECONV

#include <utility>
#include <iostream>
#include <math.h>

namespace Tensor {

    typedef unsigned int uint;

    class Shape {
        public:
            uint _d1;
            uint _d2;
            uint _d3;

            Shape() {
                _d1 = 0;
                _d2 = 0;
                _d3 = 0;
            }

            Shape(uint d1, uint d2, uint d3) {
                _d1 = d1;
                _d2 = d2;
                _d3 = d3;
            }

            Shape(const Shape& s) {
                _d1 = s._d1;
                _d2 = s._d2;
                _d3 = s._d3;
            }

            Shape& operator = (const Shape& other) {
                _d1 = other._d1;
                _d2 = other._d2;
                _d3 = other._d3;
            }

            friend std::ostream& operator << (std::ostream& str, const Shape& s) {
                str << "(" << s._d1 << ", " << s._d2 << ", " << s._d3 << ")";
                return str;
            }
    };

    template <class T>
        class Tensor3D {
            private:
                T*** _data;
                Shape _shape;

                void _delete() {
                    for (uint i = 0; i < _shape._d1; ++i) {
                        for (uint j = 0; j < _shape._d2; ++j) {
                            delete [] _data[i][j];
                        }
                        delete [] _data[i];
                    }
                    delete [] _data;
                }

                void _copy(const Tensor3D& other) {
                    for (uint i = 0; i < _shape._d1; ++i) {
                        for (uint j = 0; j < _shape._d2; ++j) {
                            for (uint k = 0; k < _shape._d3; ++k) {
                                _data[i][j][k] = other._data[i][j][k];
                            }
                        }
                    }
                }

                void _init(const Shape& s) {
                    _shape = s;
                    _data = new T**[_shape._d1];

                    for (uint i = 0; i < _shape._d1; ++i) {
                        _data[i] = new T*[_shape._d2];
                        for (uint j = 0; j < _shape._d2; ++j)
                            _data[i][j] = new T[_shape._d3];
                    }
                }

            public:
                Tensor3D (uint d1, uint d2, uint d3) {

                    _init(Shape(d1, d2, d3));

                    for (uint i = 0; i < d1; ++i) {
                        for (uint j = 0; j < d2; ++j) {
                            for (uint k = 0; k < d3; ++k) {
                                _data[i][j][k] = 0;
                            }
                        }
                    }
                }

                Tensor3D(const Tensor3D& other) {
                    _init(other._shape);
                    _copy(other);
                }

                ~Tensor3D() {
                    _delete();
                }

                uint d1() const { return _shape._d1; }
                uint d2() const { return _shape._d2; }
                uint d3() const { return _shape._d3; }

                Shape shape() { return _shape; }

                Tensor3D& operator = (const Tensor3D& other) {
                    _delete();
                    _init(other._shape);
                    _copy(other);
                }

                std::pair<Tensor3D, Tensor3D> dsplit() const {
                    Tensor3D top(_shape._d1, _shape._d2, _shape._d3 / 2);
                    Tensor3D bottom(_shape._d1, _shape._d2, _shape._d3 / 2);

                    for( uint i = 0; i < _shape._d1; ++i) {
                        for (uint j = 0; j < _shape._d2; ++j ) {
                            for (uint k = 0; k < _shape._d3 / 2; ++k) {
                                top.at(i, j, k) = _data[i][j][k];
                            }
                            for (uint k = _shape._d3 / 2; k < _shape._d3; ++k) {
                                bottom.at(i, j, k - _shape._d3/2) = _data[i][j][k];
                            }
                        }
                    }

                    return std::make_pair(top, bottom);
                }

                Tensor3D hstack(const Tensor3D& t1) {
                    Tensor3D result(_shape._d1, _shape._d2 + t1.d2(), _shape._d3);

                    for(uint i = 0; i < _shape._d1; ++i) {
                        for (uint k = 0; k < _shape._d3; ++k) {
                            for (uint j = 0; j < _shape._d2; ++j) {
                                result.at(i, j, k) = _data[i][j][k];
                            }
                            for (uint j = _shape._d2; j < _shape._d2 + t1.d2(); ++j) {
                                result.at(i, j, k) = t1.at(i, j-_shape._d2, k);
                            }
                        }
                    }

                    return result;
                }

                Tensor3D vstack(const Tensor3D& t1) {
                    Tensor3D result(_shape._d1 + t1.d1(), _shape._d2, _shape._d3);

                    for (uint k = 0; k < _shape._d3; ++k) {
                        for (uint j = 0; j < _shape._d2; ++j) {
                            for(uint i = 0; i < _shape._d1; ++i) {
                                result.at(i, j, k) = _data[i][j][k];
                            }
                            for(uint i = _shape._d1; i < _shape._d1 + t1.d1(); ++i) {
                                result.at(i, j, k) = t1.at(i-_shape._d1, j, k);
                            }
                        }
                    }

                    return result;
                }


                Tensor3D rotate_around_x() {
                    Tensor3D rotated(_shape._d3, _shape._d2, _shape._d1);

                    for(uint i = 0; i < _shape._d1; ++i) {
                        for (uint j = 0; j < _shape._d2; ++j) {
                            for (uint k = 0; k < _shape._d3; ++k) {
                                rotated.at(_shape._d3-k-1, j, i) = _data[i][j][k];
                            }
                        }
                    }

                    return rotated;
                }

                Tensor3D rotate_around_y() {
                    Tensor3D rotated(_shape._d1, _shape._d3, _shape._d2);

                    for(uint i = 0; i < _shape._d1; ++i) {
                        for (uint j = 0; j < _shape._d2; ++j) {
                            for (uint k = 0; k < _shape._d3; ++k) {
                                rotated.at(i, k, _shape._d2-j-1) = _data[i][j][k];
                            }
                        }
                    }

                    return rotated;
                }


                T& at(uint d1, uint d2, uint d3) {
                    return _data[d1][d2][d3];
                }

                const T& at(uint d1, uint d2, uint d3) const {
                    return _data[d1][d2][d3];
                }

                friend std::ostream& operator << (std::ostream& stream, const Tensor3D& t) {
                    for (uint i = 0; i < t.d1(); ++i) {
                        stream << "[ ";
                        for (uint j = 0; j < t.d2(); ++j) {
                            stream << "[ ";
                            for (uint k = 0; k < t.d3(); ++k) {
                                stream << t.at(i, j, k) << " ";
                            }
                            stream << "]";
                        }

                        stream << " ]";
                        if(i < t.d1() - 1)
                            stream << "\n";
                    }

                    return stream;
                }
        };


}

#endif /* ifndef DECONV */
