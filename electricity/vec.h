/* Damaskinskiy Konstantin, 12.07.2016 */

#ifndef __vec_h_
#define __vec_h_

#include <vector>
#include <cmath>
#include "def.h"

/* Math namespace */
namespace mth
{
  /* Vector 2D class */
template<class Type>
  class vec
  {
  //template<class T>
  //  class matr;
  public:
    int N;
    std::vector<Type> X;  // vector coordinates

    /* Class constructor.
     * ARGUMENTS:
     *   - coordinates:
     *       Type X, Y;
     */
    vec( std::initializer_list<Type> const &L )
    {
      N = L.size();
      int i = 0;
      for (auto &l : L)
        X[i++] = l;
    } /* End of 'vec' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - coordinates:
     *       Type T;
     */
    vec( Type T, int N )
    {
     X.resize(N);
      for (auto &x : X)
        x = T;
    } /* End of 'vec' function */

    /* Base class constructor. 
     * ARGUMENTS: None.
     */
    vec( void )
    {
    } /* End of 'vec' function */

    /* Comparesment operator function.
     * ARGUMENTS:
     *   - vector to compare with:
     *       const vec &V;
     * RETURNS:
     *   (BOOL) TRUE if the same, FALSE othewise.
     */
    bool operator==( const vec<Type> &V ) const
    {
      if (V.N != N)
          return false;
      return (*this - V).GetSquaredLength() < Tollerance;
    } /* End of 'operator==' function */

    bool operator!=( const vec<Type> &V ) const {
      return !(*this == V);
    }

    /* Addition operator.
     * ARGUMENTS:
     *   - vector to add:
     *       const vec &;
     * RETURNS:
     *   (vec &) self-reference.
     */
    vec & operator+=( const vec &NewVec )
    {
      if (N != NewVec.N)
          return *this;
      for (int i = 0; i < N; i++)
        X[i] += NewVec[i];

      return *this;
    } /* End of 'operator+=' function */

    /* Addition operator.
     * ARGUMENTS:
     *   - vector to add:
     *       const vec &;
     * RETURNS:
     *   (vec) new vector.
     */
    vec operator+( const vec &NewVec ) const
    {
      auto v = *this;
      v += NewVec;
      return v;
    } /* End of 'operator+' function */

    /* Substraction operator.
     * ARGUMENTS:
     *   - vector to substract:
     *       const vec &;
     * RETURNS:
     *   (vec &) self-reference.
     */
    vec & operator-=( const vec &NewVec )
    {
      if (N != NewVec.N)
          return *this;

      for (int i = 0; i < N; i++)
        X[i] -= NewVec[i];

      return *this;
    } /* End of 'operator-=' function */

    /* Substaction operator.
     * ARGUMENTS:
     *   - vector to substract:
     *       const vec &;
     * RETURNS:
     *   (vec) new vector.
     */
    vec operator-( const vec &NewVec ) const
    {
      auto v = *this;
      v -= NewVec;
      return v;
    } /* End of 'operator-' function */

    /* Unary minus operator.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec) turned vector.
     */
    vec operator-( void ) const
    {
      vec v = *this;
      for (int i = 0; i < N; i++)
        v[i] *= -1;

      return *this;
    } /* End of 'operator-' function */

    /* Multiplication on number function.
     * ARGUMENTS:
     *   - number to multiply:
     *       Type2 Num;
     * RETURNS:
     *   (vec &) self-reference.
     */
    template<class Type2>
    vec & operator*=( Type2 Num )
    {
      for (auto &x : X)
        x *= Num;

      return *this;
    } /* End of 'operator*=' function */

    /* Multiplication on number function.
     * ARGUMENTS:
     *   - number to multiply:
     *       Type2 Num;
     * RETURNS:
     *   (vec) new vector.
     */
    template<class Type2>
    vec operator*( Type2 Num ) const
    {
      auto v = *this;
      v *= Num;
      return v;
    } /* End of 'operator*' function */

    /* Multiplication on number function.
     * ARGUMENTS:
     *   - number to multiply:
     *       Type2 Num;
     * RETURNS:
     *   (vec &) self-reference.
     */
    template<class Type2>
    vec & operator/=( Type2 Num )
    {
      if (Num == 0)
        return *this;

      for (auto &x : X)
        x /= Num;

      return *this;
    } /* End of 'operator/=' function */

    /* Multiplication on number function.
     * ARGUMENTS:
     *   - number to multiply:
     *       Type2 Num;
     * RETURNS:
     *   (vec) new vector.
     */
    template<class Type2>
    vec operator/( Type2 Num ) const
    {
      auto v = *this;
      v /= Num;
      return v;
    } /* End of 'operator*' function */

    /* Dot product function.
     * ARGUMENTS:
     *   - vector to product:
     *       const vec &NewVec;
     * RETURNS:
     *   (Type) number.
     */
    Type operator&( const vec<Type> &NewVec ) const
    {
      Type res = 0;

      for (uint i = 0; i < N; i++)
        res += X[i] * NewVec.X[i];
      return res;
    } /* End of 'operator&' function */

    Type & operator[]( int i ) {
      return X[i];
    }

    Type const & operator[]( int i ) const {
      return X[i];
    }

    /* Vector length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) vector length.
     */
    Type operator!( void ) const
    {
      return norm<2>();
    } /* End of 'operator!' function */

    template<int p>
      Type norm( void ) const {
        Type res = 0;

        for (auto &x : X)
          res += std::pow(x, p);

        res = std::pow(res, 1.0 / p);

        return res;
      }

    /* Vector squared length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) sqr vector length.
     */
    Type GetSquaredLength( void ) const
    {
      Type res = 0;
      for (auto &x : X)
        res += x * x;

      return res;
    } /* End of 'GetSquaredLength' function */

    /* Normalize vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type &) normalized vector.   
     */
    template<int p>
    vec & Normalize( void )
    {
      for (auto &x : X)
        x /= norm<p>();

      return *this;
    } /* End of 'Normalize' function */

    /* Normalizing vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) normalized vector.
     */
    vec Normalizing( void ) const
    {
      auto v = *this;

      return v.Normalize();
    } /* End of 'Normalizing' function */
  }; /* End of 'vec' class */
} /* end of 'mth' namespace */

#endif /* __vec_h_ */
