#pragma once

#include <vector>
#include <memory>

using uint = unsigned int;

namespace bf_representation {

enum class type {
  TRUTH_TABLE,
  PCNF,
  PDNF,
  RDNF,
  ZHEGALKIN
};

class base {
protected:
  uint dimension;
public:
  static uint grayEncode( uint binary ) {
    return binary ^ (binary >> 1);
  }

  static uint grayDecode( uint gray ) {
    uint b;

    for (b = 0; gray != 0; gray >>= 1)
      b ^= gray;

    return b;
  }

  static bool bool_pow( bool x, bool y ) { return x & y | ~x & ~y; }

  // LITTLE-ENDIAN (Least Significant Bit First)
  static uint binaryDecode( std::vector<bool> const &bin ) {
    uint dec = 0;

    for (uint i = 0; i < bin.size(); i++)
      dec += bin[i] * (1 << i);
  }

  base( uint dimension );

  virtual bool eval( std::vector<bool> const &argument ) const = 0;
};

class truth_table : public base {
public:
  truth_table( std::vector<bool> const &truthTable );
  bool eval(std::vector<bool> const &argument ) const final;

private:
  std::vector<bool> truthTable;
};

class perfect_disjunctive_normal_form : public base {
public:
  perfect_disjunctive_normal_form( std::vector<std::vector<bool>> const &m );
  bool eval(std::vector<bool> const &argument ) const final;

private:
  std::vector<std::vector<bool>> matrix;
};

class perfect_conjuctive_normal_form : public base {
public:
  perfect_conjuctive_normal_form( std::vector<std::vector<bool>> const &m );
  bool eval(std::vector<bool> const &argument ) const final;
private:
  std::vector<std::vector<bool>> matrix;
};
}

class bool_function {
private:
  std::shared_ptr<bf_representation::base> representation;

public:
  bool_function( std::shared_ptr<bf_representation::base> r ) : representation(r) {}
};
