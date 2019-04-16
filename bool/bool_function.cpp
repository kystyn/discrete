#include <cmath>
#include "bool_function.h"

bf_representation::base::base( uint dimension ) : dimension(dimension) {}

/*** Truth table ***/
bool bf_representation::truth_table::eval(std::vector<bool> const &argument ) const {
  return truthTable[base::binaryDecode(argument)];
}

bf_representation::truth_table::truth_table( std::vector<bool> const &truthTable ) :
  base(log2(truthTable.size())), truthTable(truthTable) {}

/*** Perfect disjunctive noemal form ***/
bf_representation::perfect_disjunctive_normal_form::perfect_disjunctive_normal_form( std::vector<std::vector<bool>> const &m ) : 
    base(m.size() != 0 ? log2(m[0].size()) : 0), matrix(m) {}

bool bf_representation::perfect_disjunctive_normal_form::eval(std::vector<bool> const &argument ) const {
  bool res = false;

  if (argument.size() != dimension)
    throw "PDNF::eval : bad argument";

  for (auto &&sign : matrix) {
    bool localRes = false;

    for (uint i = 0; i < dimension; i++)
      localRes &= bool_pow(argument[i], sign[i]);

    res |= localRes;
  }

  return res;
}

/*** Perfect conjuctive normal form ***/
bf_representation::perfect_conjuctive_normal_form::perfect_conjuctive_normal_form( std::vector<std::vector<bool>> const &m ) :
  base(m.size() != 0 ? log2(m[0].size()) : 0), matrix(m) {}

bool bf_representation::perfect_conjuctive_normal_form::eval(std::vector<bool> const &argument ) const {
  bool res = true;

  if (argument.size() != dimension)
    throw "PCNF::eval : bad argument";

  for (auto &&sign : matrix) {
    bool localRes = false;

    for (uint i = 0; i < dimension; i++)
      localRes |= bool_pow(argument[i], sign[i]);

    res &= localRes;
  }

  return res;
}