#include "carnaugh_map.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"

bf_representation::carnaugh_map::carnaugh_map( std::vector<std::vector<bool>> const &m ) :
  base(m.size() == 0 ? 0 : (uint)log2(m.size() * m[0].size()), "C"), map(m) {}

bool bf_representation::carnaugh_map::eval( std::vector<bool> const &arg ) const {
  std::vector<bool> argX((dimension + 1) / 2);

  for (uint i = 0; i < (dimension + 1) / 2; i++)
    argX[i] = false;

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
    convertToPDNF((pdnf &)b);
  else if (b.getSpecificator() == "RDNF")
    convertToPDNF((pdnf &)b);
}

void bf_representation::carnaugh_map::convertToPDNF( pdnf &p ) const {
  std::vector<std::vector<bool>> matrix;

  for (uint y = 0; y < (1 << ((dimension + 1) / 2)); y++)
    for (uint x = 0; x < (1 << (dimension / 2)); x++)
      if (map[y][x]) {
        auto
          binX = base::binaryEncode(base::grayEncode(x)),
          binY = base::binaryEncode(base::grayEncode(y));

        for (auto y : binY)
          binX.push_back(y);

        matrix.push_back(binX);
      }

  p = pdnf(matrix, dimension);
}

void bf_representation::carnaugh_map::convertToRDNF( rdnf &p ) const {
  std::vector<std::vector<bool>> matrix;

  // horizontal loop
  for (uint y = 1; y < (1 << ((dimension + 1) / 2)); y++)
    for (uint x = 1; x < (1 << (dimension / 2)); x++) {

    }
}