#include "perfect_cnf.h"

bf_representation::perfect_conjuctive_normal_form::perfect_conjuctive_normal_form( std::vector<std::vector<bool>> const &m ) :
  base(m.size() != 0 ? m[0].size() : 0, "RDNF"), matrix(m) {}

bool bf_representation::perfect_conjuctive_normal_form::eval(std::vector<bool> const &argument ) const {
  bool res = false;

  if (argument.size() != dimension)
    throw "PCNF::eval : bad argument";

  for (auto &&sign : matrix) {
    bool localRes = true;

    for (uint i = 0; i < dimension; i++)
      localRes |= bool_pow(argument[i], sign[i]);

    res &= localRes;
  }

  return res;
}
