#include "carnaugh_map.h"

bf_representation::carnaugh_map::carnaugh_map( std::vector<std::vector<bool>> const &m ) :
  base(m.size() == 0 ? 0 : (uint)log2(m.size() * m[0].size()), "C"), map(m) {}

bool bf_representation::carnaugh_map::eval( std::vector<bool> const &arg ) const {
  std::vector<bool> argX((dimension + 1) / 2);

  for (uint i = 0; i < (dimension + 1) / 2; i++)
    argX[i] = false;

  uint
    x = base::grayEncode(base::binaryDecode(argX)),
    y = base::grayEncode(base::binaryDecode(arg) >> ((dimension + 1) / 2));

  return map[y][x];
}

void bf_representation::carnaugh_map::output( std::ostream &os ) const {
  for (auto y : map) {
    for (auto x : y)
      os << x;
    os << std::endl;
  }
}