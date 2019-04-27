#include "carnaugh_map.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"

bf_representation::carnaugh_map::carnaugh_map( std::vector<std::vector<bool>> const &m ) :
  base(m.size() == 0 ? 0 : (uint)log2(m.size() * m[0].size()), "C"), map(m) {}

bool bf_representation::carnaugh_map::eval( std::vector<bool> const &arg ) const {
  std::vector<bool> argX(dimension / 2);

  for (uint i = 0; i < dimension/ 2; i++)
    argX[i] = arg[dimension - 1 - i];

  uint
    x = base::grayEncode(base::binaryDecode(argX)),
    y = base::grayEncode(base::binaryDecode(arg) >> (dimension / 2));

  return map[y][x];
}

void bf_representation::carnaugh_map::output( std::ostream &os ) const {
  for (auto y : map) {
    for (auto x : y)
      os << x;
    os << std::endl;
  }
}

void bf_representation::carnaugh_map::convert( bf_representation::base &b ) const {
  if (b.getSpecificator() == "TT")
    convertToTruthTable((truth_table &)b);
  else if (b.getSpecificator() == "PDNF")
    convertToPerfectNF<pdnf>((pdnf &)b);
  else if (b.getSpecificator() == "PCNF")
    convertToPerfectNF<pcnf>((pcnf &)b);
  else if (b.getSpecificator() == "RDNF") {
    pdnf p;
    convertToPerfectNF<pdnf>(p);
    p.convert((rdnf &)b);
  }
}