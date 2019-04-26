#include "truth_table.h"
#include "perfect_cnf.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "zhegalkin.h"

bf_representation::zhegalkin::zhegalkin( std::vector<bool> const &coefficients ) :
  base(coefficients.size() == 0 ? 0 : (uint)log2(coefficients.size()), "Z"),
  coefficients(coefficients) {}

bool bf_representation::zhegalkin::eval( std::vector<bool> const &argument ) const {
  bool res = coefficients[0];

  std::vector<bool> sign(dimension, false);

  for (uint i = 1; i < (1 << dimension); i++) {
    bool localRes = true;
    genNextBinary(sign);

    if (coefficients[i]) {
      for (uint j = 0; j < dimension; j++)
        if (sign[j])
          localRes &= argument[j];

      res = res ^ localRes;
    }
  }

  return res;
}

void bf_representation::zhegalkin::convert( base &b ) const {
  if (b.getSpecificator() == "TT")
     convertToTruthTable((truth_table &)b);
  else if (b.getSpecificator() == "PDNF") {
    truth_table t;
    convertToTruthTable(t);
    t.convert((pdnf &)b);
  }
  else if (b.getSpecificator() == "RDNF") {
    truth_table t;
    convertToTruthTable(t);
    t.convert((rdnf &)b);
  }
  else if (b.getSpecificator() == "PCNF") {
    truth_table t;
    convertToTruthTable(t);
    t.convert((pcnf &)b);
  }
}

void bf_representation::zhegalkin::output( std::ostream &os ) const {
  for (auto x : coefficients)
    os << x << ' ';
  os << std::endl;
}