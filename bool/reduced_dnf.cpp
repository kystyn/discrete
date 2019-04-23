#include "reduced_dnf.h"

bf_representation::reduced_disjunctuve_normal_form::reduced_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m ) :
  base(m.size() != 0 ? m[0].size() / 2 : 0, "RDNF"), matrix(m) {
}

bool bf_representation::reduced_disjunctuve_normal_form::eval(std::vector<bool> const &argument ) const {
  auto arg = argument;
  bool res = false;

  for (uint i = 0, n = arg.size(); i < n; i++)
    arg.push_back(!arg[i]);

  for (auto &&sign : matrix) {
    bool localRes = true;

    for (uint i = 0; i < 2 * dimension; i++)
      if (sign[i])
        localRes &= arg[i];

    res |= localRes;
  }
  return res;
}

void bf_representation::reduced_disjunctuve_normal_form::output( std::ostream &os ) const {
  for (auto y : matrix) {
    for (auto x : y)
      std::cout << x << ' ';
    std::cout << std::endl;
  }
}
