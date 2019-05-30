#pragma once

#include <vector>
#include <cmath>

#include "def.h"

/* Matrix class */
namespace mth {
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

  virtual T operator()( uint y, uint x ) const { return x + y; }
  virtual T & operator()( uint y, uint x ) { return x + y; }

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
  matr & operator*=( double Num ) {

    for (unsigned int i = 0; i < H; i++)
      for (unsigned int j = 0; j < W; j++)
        (*this)(i, j) *= Num;

    return *this;
  }

  double operator!( void ) const {
    double n = 0;

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
template<typename T1, typename MatrType1,
         typename T2, typename MatrType2,
         typename ResultMatrType, typename T3,
         typename = typename std::enable_if<
             std::is_base_of<MatrType1, mth::matr<T1>>::value &&
             std::is_base_of<MatrType2, mth::matr<T2>>::value &&
             std::is_base_of<ResultMatrType, mth::matr<T3>>::value>::type>
ResultMatrType operator*( MatrType1 const &A, MatrType2 const &B ) {
  if (A.W != B.H)
    throw "matr * matr: size mismatch\n";

  ResultMatrType C(A.H, B.W);

  for (unsigned int i = 0; i < A.H; i++)
    for (unsigned int j = 0; j < B.W; j++)
    {
      C(i, j) = 0;
      for (unsigned int k = 0; k < B.W; k++)
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
template<typename T, typename MatrType,
         typename = typename std::enable_if<
             std::is_base_of<T, MatrType>::value>::type>
MatrType operator*( MatrType M, T Num ) {
  MatrType C = M;

  for (unsigned int i = 0; i < M.H; i++)
    for (unsigned int j = 0; j < M.W; j++)
      C(i, j) *= Num;

  return C;
}

template<typename T1, typename MatrType1,
         typename T2, typename MatrType2,
         typename ResultMatrType, typename T3,
         typename = typename std::enable_if<
             std::is_base_of<MatrType1, mth::matr<T1>>::value &&
             std::is_base_of<MatrType2, mth::matr<T2>>::value &&
             std::is_base_of<ResultMatrType, mth::matr<T3>>::value>::type>
ResultMatrType operator+( MatrType1 const &A, MatrType2 const &B ) {
  if (A.H != B.H && A.W != B.W)
    throw "matr + matr: size mismatch\n";

  ResultMatrType C(A.H, A.W);
  for (unsigned int i = 0; i < A.H; i++)
    for (unsigned int j = 0; j < A.W; j++)
      C(i, j) = A(i, j) + B(i, j);

  return C;
}

template<typename T1, typename MatrType1,
         typename T2, typename MatrType2,
         typename ResultMatrType, typename T3,
         typename = typename std::enable_if<
             std::is_base_of<MatrType1, mth::matr<T1>>::value &&
             std::is_base_of<MatrType2, mth::matr<T2>>::value &&
             std::is_base_of<ResultMatrType, mth::matr<T3>>::value>::type>
ResultMatrType operator-( MatrType1 const &A, MatrType2 const &B ) {
  if (A.H != B.H && A.W != B.W)
    throw "matr + matr: size mismatch\n";

  ResultMatrType C(A.H, A.W);
  for (unsigned int i = 0; i < A.H; i++)
    for (unsigned int j = 0; j < A.W; j++)
      C(i, j) = A(i, j) - B(i, j);

  return C;
}

template<typename T, typename MatrType,
         typename = typename std::enable_if<
             std::is_base_of<T, MatrType>::value>::type>
MatrType transposing( MatrType A ) {
  MatrType At(A.W, A.H);

  for (unsigned int i = 0; i < A.W; i++)
    for (unsigned int j = 0; j < A.H; j++)
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
template<typename T1, typename MatrType1,
         typename T,
         typename = typename std::enable_if<
             std::is_base_of<MatrType1, matr<T1>>::value >::type>
vec<T> operator*( MatrType1 const &A, vec<T> const &b ) {
  int i, j;

  if (A.W != b.getN())
    throw "matr * vec: size mismatch\n";

  vec<T> x(A.H);

  for (i = 0; i < A.H; i++) {
    double r = 0;
    for (j = 0; j < A.W; j++) {
      r += A(i, j) * b[j];
    }
    x[i] = r;
  }

  return x;
}
}
