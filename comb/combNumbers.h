#pragma once

#include <vector>
#include "myuint.h"

class combNumbers {
private:
  void genStirling2Table( std::vector<std::vector<myuint32>> &table, unsigned int m, unsigned int n );
public:
  myuint32 C( unsigned int m, unsigned int n );
  myuint32 U( unsigned int m, unsigned int n );
  myuint32 A( unsigned int m, unsigned int n );
  myuint32 S( unsigned int m, unsigned int n );
  myuint32 B( unsigned int n );
  myuint32 P( unsigned int n );
};
