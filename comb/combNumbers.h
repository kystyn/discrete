#pragma once

#include <vector>
#include "myuint.h"

class combNumbers {
private:
  static std::vector<myuint32> genStirlingString( uint m, uint n );
public:
  static myuint32 C( unsigned int m, unsigned int n );
  static myuint32 U( unsigned int m, unsigned int n );
  static myuint32 A( unsigned int m, unsigned int n );
  static myuint32 S( unsigned int m, unsigned int n );
  static myuint32 B( unsigned int n );
  static myuint32 P( unsigned int n );
};
