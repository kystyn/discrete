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
  virtual void output( std::ostream &os ) const = 0;

  virtual void convert( base &b ) const {}
  /*virtual void convertPDNF( std::shared_ptr<perfect_disjunctuve_normal_form> b ) const {}
  virtual void convert( std::shared_ptr<perfect_conjuctive_normal_form> b ) const {}
  virtual void convert( std::shared_ptr<reduced_disjunctuve_normal_form> b ) const {}
  virtual void convert( std::shared_ptr<truth_table> &&b ) const {}                        */

public:
  base( uint dimension, std::string const &spec ) : dimension(dimension), specificator(spec) {}

  std::string getSpecificator( void ) const { return specificator; }

  static uint grayEncode( uint binary ) {
    return binary ^ (binary >> 1);
  }

  static uint grayDecode( uint gray ) {
    uint b;

    for (b = 0; gray != 0; gray >>= 1)
      b ^= gray;

    return b;
  }

  static bool bool_pow( bool x, bool y ) { return x == y; }

  // LITTLE-ENDIAN (Least Significant Bit First)
  static std::vector<bool> binaryEncode( uint dec, uint encodedSize = 0 )  {
    std::vector<bool> bin;

    do {
      bin.push_back(dec & 1);
      dec >>= 1;
    } while (dec != 0);

    while (bin.size() < encodedSize)
      bin.push_back(false);

    return bin;
  }

  static uint binaryDecode( std::vector<bool> const &bin ) {
    uint dec = 0;
  
    for (uint i = 0; i < bin.size(); i++)
      dec += bin[i] * (1 << i);
  
    return dec;
  }
};
}
