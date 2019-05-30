#pragma once

#include <vector>
#include <cmath>
#include <type_traits>

#include "def.h"

/* Matrix class */
namespace mth {

// forward declaration
template<typename MatrType>
MatrType operator*( MatrType const &A, MatrType const &B );

template<typename T>
class matr {
protected:
  size_t H, W;

public:
  matr() : H(0), W(0) {}

  matr( matr const &B ) {
    H = B.H;
    W = B.W;
  }

  matr & operator=( matr const &B ) {
    H = B.H;
    W = B.W;

    return *this;
  }

  matr( size_t H, size_t W = 0 ) : H(H), W(W) {
    if (W == 0)
        this->W = H;
  }

  size_t getW() const { return W; }
  size_t getH() const { return H; }

  virtual void reset( uint NewH, uint NewW ) {}
  virtual T operator()( uint y, uint x ) const { return (T)0; }
  virtual T & operator()( uint y, uint x ) { T t; return t; }

  /* Matrix mul vector function.
   * ARGUMENTS:
   *   matrix (H x W);
   *   vector (W);
   *   M, N;
   * RETURNS: vector (M).
   */
  vec<T> operator*( vec<T> const &b ) const;

  matr & operator+=( matr const &B ) {
    if (H != B.H && W != B.W)
      throw "matr + matr: size mismatch\n";

    for (unsigned int i = 0; i < H; i++)
      for (unsigned int j = 0; j < W; j++)
        (*this)(i, j) += B(i, j);

    return *this;
  }

  matr & operator-=( matr const &B ) {
    if (H != B.H && W != B.W)
      throw "matr + matr: size mismatch\n";

    for (unsigned int i = 0; i < H; i++)
      for (unsigned int j = 0; j < W; j++)
        (*this)(i, j) -= B(i, j);

    return *this;
  }

  /* Matrix mul matrix function.
   * ARGUMENTS:
   *   matrix (M x N), (N X K);
   *   M, N, K;
   * RETURNS: matrix (M X K).
   */
  matr & operator*=( T Num ) {

    for (unsigned int i = 0; i < H; i++)
      for (unsigned int j = 0; j < W; j++)
        (*this)(i, j) *= Num;

    return *this;
  }

  T operator!( void ) const {
    T n = 0;

    for (unsigned int i = 0; i < H; i++)
      for (unsigned int j = 0; j < W; j++)
        n += (*this)(i, j) * (*this)(i, j);
    
    return sqrt(n);
  }
};

/* Matrix mul matrix function.
 * ARGUMENTS:
 *   matrix (M x N), (N X K);
 *   M, N, K;
 * RETURNS: matrix (M X K).
 */
template<typename MatrType>
MatrType operator*( MatrType const &A, MatrType const &B ) {
  if (A.getW() != B.getH())
    throw "matr * matr: size mismatch\n";

  MatrType C(A.getH(), B.getW());

  for (unsigned int i = 0; i < A.getH(); i++)
    for (unsigned int j = 0; j < B.getW(); j++)
    {
      C(i, j) = 0;
      for (unsigned int k = 0; k < A.getW(); k++)
        C(i, j) += A(i, k) * B(k, j);
    }

  return C;
}

/* Matrix mul matrix function.
 * ARGUMENTS:
 *   matrix (M x N), (N X K);
 *   M, N, K;
 * RETURNS: matrix (M X K).
 */
template<typename MatrType, typename T>
MatrType operator*( MatrType M, T Num ) {
  MatrType C = M;

  for (unsigned int i = 0; i < M.getH(); i++)
    for (unsigned int j = 0; j < M.getW(); j++)
      C(i, j) *= Num;

  return C;
}

template<typename MatrType>
MatrType operator+( MatrType const &A, MatrType const &B ) {
  if (A.getH() != B.getH() && A.getW() != B.getW())
    throw "matr + matr: size mismatch\n";

  MatrType C(A.getH(), A.getW());
  for (unsigned int i = 0; i < A.getH(); i++)
    for (unsigned int j = 0; j < A.getW(); j++)
      C(i, j) = A(i, j) + B(i, j);

  return C;
}

template<typename MatrType>
MatrType operator-( MatrType const &A, MatrType const &B ) {
  if (A.getH() != B.getH() && A.getW() != B.getW())
    throw "matr + matr: size mismatch\n";

  MatrType C(A.getH(), A.getW());
  for (unsigned int i = 0; i < A.getH(); i++)
    for (unsigned int j = 0; j < A.getW(); j++)
      C(i, j) = A(i, j) - B(i, j);

  return C;
}

template<typename MatrType>
MatrType transposing( MatrType const &A ) {
  MatrType At(A.getW(), A.getH());

  for (unsigned int i = 0; i < A.getW(); i++)
    for (unsigned int j = 0; j < A.getH(); j++)
      At(i, j) = A(j, i);

  return At;
}

/* Matrix mul vector function.
 * ARGUMENTS:
 *   matrix (H x W);
 *   vector (W);
 *   M, N;
 * RETURNS: vector (M).
 */
template<typename MatrType,
         typename T>
vec<T> operator*( MatrType const &A, vec<T> const &b ) {
  int i, j;

  if (A.getW() != b.getN())
    throw "matr * vec: size mismatch\n";

  vec<T> x(A.getH());

  for (i = 0; i < A.getH(); i++) {
    double r = 0;
    for (j = 0; j < A.getW(); j++) {
      r += A(i, j) * b[j];
    }
    x[i] = r;
  }

  return x;
}

template<typename MatrType>
MatrType & operator*=( MatrType &A, MatrType const &B ) {
  if (A.getW() != B.getH())
    throw "matr * matr: size mismatch\n";

  A = A * B;

  return A;
}
}
