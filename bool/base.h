#pragma once

#include "def.h"

class bool_function;

namespace bf_representation {

class base {
  friend class ::bool_function;
protected:
  uint dimension;
  std::string specificator;

  virtual bool eval( std::vector<bool> const &argument ) const = 0;
  virtual void input( std::istream &is ) = 0;
  virtual void output( std::ostream &os ) const = 0;
  virtual void convert( base &b ) const {}
  void  convertToTruthTable ( bf_representation::truth_table &b ) const;

public:
  base( uint dimension, std::string const &spec ) : dimension(dimension), specificator(spec) {}

  std::string getSpecificator( void ) const;

  static uint grayEncode( uint binary );
  static uint grayDecode( uint gray );
  static bool bool_pow( bool x, bool y );

  // LITTLE-ENDIAN (Least Significant Bit First)
  static std::vector<bool> binaryEncode( uint dec, uint encodedSize = 0 );
  static void genNextBinary(std::vector<bool> &bin );
  static uint binaryDecode( std::vector<bool> const &bin );
};

std::istream & operator>>( std::istream &is, std::vector<bool> &v );
std::ostream & operator<<( std::ostream &os, std::vector<std::vector<bool>> const &v );
std::ostream & operator<<( std::ostream &os, std::vector<bool> const &v );
std::vector<bool> operator*( std::vector<bool> const &v1, std::vector<bool> const &v2 );
std::vector<bool> operator*( std::vector<bool> const &v1, bool v2 );
}
