#pragma once

#include <ostream>

class myuint32 {
private:
  friend std::ostream & operator<<( std::ostream &, myuint32 const & );

  unsigned int number;
  const unsigned int MaxInt;

public:
  myuint32( void ) : number(0), MaxInt(0xFFFFFFFF) {}

  myuint32( unsigned int number ) : number(number), MaxInt(0xFFFFFFFF) {}

  myuint32( myuint32 const &num ) : number(num.number), MaxInt(0xFFFFFFFF) {}

  myuint32 & operator=( unsigned int num ) {
    number = num;
    return *this;
  }

  myuint32 & operator=( myuint32 const &num ) {
    number = num.number;
    return *this;
  }

  myuint32 operator+( myuint32 n ) const {
    if (MaxInt - n.number > number)
      return myuint32(number + n.number);
    throw "UINT overflow";
  }

  myuint32 operator*( myuint32 n ) const {
    if (number == 0)
      return 0;

    if (double(MaxInt / n.number) > number)
      return myuint32(number * n.number);

    throw "UINT overflow";
  }

  myuint32 & operator*=( myuint32 n ) {
    if (n.number == 0)
      return *this;
    if (double(MaxInt / n.number) > number)
      number *= n.number;
    else
      throw "UINT overflow";
    return *this;
  }

  myuint32 operator-( myuint32 n ) const {
    if (number >= n.number)
      return myuint32(number - n.number);
    throw "UINT underflow";
  }

  myuint32 & operator+=( myuint32 n ) {
    if (MaxInt - n.number > number)
      number += n.number;
    else
      throw "UINT overflow";

    return *this;
  }

  myuint32 & operator++( void ) {
    if (MaxInt - 1 > number)
      number++;
    else
      throw "UINT overflow";

    return *this;
  }

  myuint32 & operator++( int n ) {
    if (MaxInt - 1 > number)
      ++number;
    else
      throw "UINT overflow";

    return *this;
  }

  myuint32 & operator-=( myuint32 n ) {
    if (number >= n.number)
      number -= n.number;
    else
      throw "UINT underflow";

    return *this;
  }

  myuint32 operator/( myuint32 n ) const {
    return myuint32(number / n.number);
  }

  myuint32 & operator/=( myuint32 n ) {
    number /= n.number;
    return *this;
  }

  bool operator<( myuint32 n ) const {
    return number < n.number;
  }
  
  bool operator<=( myuint32 n ) const {
    return number <= n.number;
  }
  
  bool operator>( myuint32 n ) const {
    return number > n.number;
  }
  
  bool operator>=( myuint32 n ) const {
    return number >= n.number;
  }

  explicit operator unsigned int( void ) {
    return number;
  }
};
