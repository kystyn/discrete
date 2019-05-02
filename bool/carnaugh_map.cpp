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

void bf_representation::carnaugh_map::input( std::istream &is ) {
  is >> dimension;
  map.resize(dimension / 2);

  for (auto &x : map)
    x.resize((dimension + 1) / 2);

  for (auto &y : map)
    is >> y;
}

void bf_representation::carnaugh_map::output( std::ostream &os ) const {
  /* header */
  for (uint x = 0; x < dimension; x++)
    os << ' ';
  for (uint i = 0, n = (1 << ((dimension + 1) / 2)); i < n; i++) {
    auto sign = base::binaryEncode(base::grayEncode(i), (dimension + 1) / 2);

    for (auto x : sign)
      os << x;
    os << ' ';
  }

  os << std::endl;

  /* values */
  for (uint i = 0, n = (1 << (dimension / 2)); i < n; i++) {
    /* signature */
    auto sign = base::binaryEncode(base::grayEncode(i), dimension / 2);
    for (auto x : sign)
      os << x;

    for (uint j = 0, m = (1 << ((dimension + 1) / 2)); j < m; j++) {
      for (uint x = 0; x < (dimension + 1) / 2; x++)
        os << ' ';
      os << map[i][j];
    }
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
  else if (b.getSpecificator() == "Z") {
    truth_table tt;
    convertToTruthTable(tt);
    tt.convert((zhegalkin &)b);
  }
}