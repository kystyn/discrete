#include "carnaugh_map.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "truth_table.h"
#include "zhegalkin.h"

bf_representation::carnaugh_map::carnaugh_map( std::vector<std::vector<bool>> const &m, uint dim ) :
  base(m.size() == 0 ? dim : (uint)log2(m.size() * m[0].size()), "C"), map(m) {}

bool bf_representation::carnaugh_map::eval( std::vector<bool> const &arg ) const {
  std::vector<bool>
    argX((dimension + 1) / 2),
    argY(dimension / 2);

  for (uint i = dimension / 2; i < dimension; i++)
    argX[i - dimension / 2] = arg[i];

  for (uint i = 0; i < dimension / 2; i++)
    argY[i] = arg[i];

  uint
    x = base::grayEncode(base::binaryDecode(argX)),
    y = base::grayEncode(base::binaryDecode(argY));

  return map[y][x];
}

void bf_representation::carnaugh_map::output( std::ostream &os ) const {
  os << map;
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
  else if (b.getSpecificator() == "Z") {
    truth_table tt;
    convertToTruthTable(tt);
    tt.convert((zhegalkin &)b);
  }
}