#include "zhegalkin.h"

bf_representation::zhegalkin::zhegalkin( std::vector<bool> const &coefficients ) :
  base(coefficients.size() == 0 ? 0 : (uint)log2(coefficients.size()), "Zhegalkin"),
  coefficients(coefficients) {}

bool bf_representation::zhegalkin::eval( std::vector<bool> const &argument ) const {
  bool res = false;

  /// LITTLE ENDIAN
  auto nextNarNotation = [this]( std::vector<uint> &number, uint n ) {
    std::vector<uint> res;

    bool add = true;
    for (uint i = 0, sz = number.size(); i < sz; i++)
      if (number[i] + add == n - 1) {
        number[i] = 0;
        add = true;
      }
      else {
        number[i]++;
        add = false;
      }

    /*if (add)
      number.push_back*/
    return res;
  };

  return res;
}