#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <vector>
#include <map>
#include "matr.h"

namespace mth {
template<typename T>
class sparse_matrix : public matr<T> {
public:
    sparse_matrix( std::vector<std::map<uint, T>> const &M ) :
        Matrix(M) {}

    sparse_matrix( uint H, uint W = 0 ) : matr<T>(H, W) {
        Matrix.resize(H);
    }

    T operator()( uint y, uint x ) const {
        if (x < 0 || x >= matr<T>::W || y < 0 || y >= matr<T>::H)
            throw "Bad index";

        std::map<uint, T>::const_iterator it;

        if ((it = Matrix[y].find(x)) != Matrix[x].end())
            return *it;
        return 0;
    }

    T & operator()( uint y, uint x ) {
        return Matrix[y][x];
    }

private:
    std::vector<std::map<uint, T>> Matrix;
};
} // mth end

#endif // SPARSE_MATRIX_H
