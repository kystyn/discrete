#include "truth_table.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "perfect_cnf.h"
#include "zhegalkin.h"
#include "carnaugh_map.h"

bf_representation::truth_table::truth_table( std::vector<bool> const &truthTable ) :
  base(truthTable.size() != 0 ? (uint)log2(truthTable.size()) : 0, "TT"), truthTable(truthTable) {
  if ((uint)(1 << dimension) != truthTable.size() && truthTable.size() != 0)
    std::cerr << "TT constructor :: bad truth table!";
}

void bf_representation::truth_table::input( std::istream &is ) {
  is >> dimension;
  truthTable.resize((uint)(1 << dimension));
  is >> truthTable;
}

void bf_representation::truth_table::output( std::ostream &os ) const {
  for (uint i = 0, n = truthTable.size(); i < n; i++) {
    os << base::binaryEncode(i, dimension) << '|' << truthTable[i] << '\n';
  }
}

bool bf_representation::truth_table::eval(std::vector<bool> const &argument ) const {
  if (argument.size() != dimension)
    throw "truth table :: eval : bad argument!";
  return truthTable[base::binaryDecode(argument)];
}

void bf_representation::truth_table::convert( bf_representation::base &b ) const {
  if (b.getSpecificator() == "PDNF") 
    convertToPDNF((pdnf &)b);
  else if (b.getSpecificator() == "RDNF")
    convertToRDNF((rdnf &)b);
  else if (b.getSpecificator() == "PCNF")
    convertToPCNF((pcnf &)b);
  else if (b.getSpecificator() == "Z")
    convertToZhegalkin((zhegalkin &)b);
  else if (b.getSpecificator() == "C")
    convertToCarnaughMap((carnaugh_map &)b);
}

void bf_representation::truth_table::convertToPDNF( pdnf &p ) const {
  std::vector<std::vector<bool>> m;

  m.reserve((uint)(1 << dimension));

  for (uint i = 0; i < (uint)(1 << dimension); i++)
    if (truthTable[i])
      m.push_back(base::binaryEncode(i, dimension));

  m.shrink_to_fit();

  p = pdnf(m, dimension);
}

void bf_representation::truth_table::convertToRDNF( rdnf &r ) const {
  pdnf p;
  convertToPDNF(p);
  p.convert(r);
}

void bf_representation::truth_table::convertToZhegalkin( zhegalkin &zh ) const {
  std::vector<bool> coeffs((uint)(1 << dimension), false), cur = coeffs;
  auto prev = truthTable;

  coeffs[0] = truthTable[0];

  for (uint i = 1; i < (uint)(1 << dimension); i++) {
    for (uint j = 0; j < (uint)(1 << dimension) - i; j++)
      cur[j] = prev[j + 1] ^ prev[j];
    coeffs[i] = cur.front();
    prev = cur;
  }

  zh = coeffs;
}

void bf_representation::truth_table::convertToPCNF( pcnf &p ) const {
  std::vector<std::vector<bool>> m;

  for (uint i = 0; i < (uint)(1 << dimension); i++) {
    auto arg = base::binaryEncode(i, dimension), oldarg = arg;

    for (auto &x : arg)
      x = !x;

    if (truthTable[base::binaryDecode(arg)])
      m.push_back(arg);
  }

  p = pcnf(m, dimension);
}

void bf_representation::truth_table::convertToCarnaughMap( carnaugh_map &cMap ) const {
  std::vector<std::vector<bool>> matrix((uint)(1 << (dimension / 2)));

  for (auto &x : matrix)
    x.resize((uint)(1 << ((dimension + 1) / 2)));

  for (uint y = 0, n = matrix.size(); y < n; y++)
    for (uint x = 0, m = matrix[0].size(); x < m; x++) {   //x, y are Gray codes numbers
      auto
          binX = base::binaryEncode(base::grayEncode(x), (dimension + 1) / 2),
          binY = base::binaryEncode(base::grayEncode(y), dimension / 2);

      for (auto x : binX)
        binY.push_back(x);

      matrix[y][x] = truthTable[base::binaryDecode(binY)];
    }
  cMap = carnaugh_map(matrix, dimension);
}

std::vector<bool> const & bf_representation::truth_table::getTable( void ) const {
  return truthTable;
}
