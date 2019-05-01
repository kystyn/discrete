#include "truth_table.h"
#include "reduced_dnf.h"
#include "perfect_cnf.h"
#include "zhegalkin.h"
#include "carnaugh_map.h"

bf_representation::reduced_disjunctuve_normal_form::reduced_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m, uint dim ) :
  base(m.size() != 0 ? m[0].size() / 2 : dim, "RDNF"), matrix(m) {
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
  os << matrix;
}

void bf_representation::reduced_disjunctuve_normal_form::convert( base &b ) const {
  if (b.getSpecificator() == "TT")
     convertToTruthTable((truth_table &)b);
  else if (b.getSpecificator() == "PDNF") {
    truth_table tt;
    convertToTruthTable(tt);
    tt.convert((pdnf &)b);
  }
  else if (b.getSpecificator() == "PCNF") {
    truth_table tt;
    convertToTruthTable(tt);
    tt.convert((pcnf &)b);
  }
  else if (b.getSpecificator() == "Z") {
    truth_table tt;
    convertToTruthTable(tt);
    tt.convert((zhegalkin &)b);
  }
  else if (b.getSpecificator() == "C") {
    truth_table tt;
    convertToTruthTable(tt);
    tt.convert((carnaugh_map &)b);
  }
}
