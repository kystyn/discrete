#include "truth_table.h"
#include "perfect_cnf.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "zhegalkin.h"
#include "carnaugh_map.h"

bf_representation::zhegalkin::zhegalkin( std::vector<bool> const &coefficients ) :
  base(coefficients.size() == 0 ? 0 : (uint)log2(coefficients.size()), "Z"),
  coefficients(coefficients) {}

bool bf_representation::zhegalkin::eval( std::vector<bool> const &argument ) const {
  bool res = coefficients[0];

  std::vector<bool> sign(dimension, false);

  for (uint i = 1; i < (uint)(1 << dimension); i++) {
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
  else if (b.getSpecificator() == "C") {
    truth_table t;
    convertToTruthTable(t);
    t.convert((carnaugh_map &)b);
  }
}

void bf_representation::zhegalkin::input( std::istream &is ) {
  is >> dimension;
  coefficients.resize((uint)(1 << dimension));
  is >> coefficients;
}

void bf_representation::zhegalkin::output( std::ostream &os ) const {
  if (coefficients[0])
    os << "1 ^\n";
  for (uint i = 1, n = coefficients.size(); i < n; i++)
    if (coefficients[i]) {
      auto sign = base::binaryEncode(i, dimension);

      for (uint j = 0; j < dimension; j++)
        if (sign[j])
          os << 'x' << j;

      if (i != n - 1)
        os << " ^\n";
      else
        os << "\n";
    }
}

std::vector<bool> const & bf_representation::zhegalkin::getCoeffs( void ) const {
  return coefficients;
}