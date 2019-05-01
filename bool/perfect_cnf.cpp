#include "truth_table.h"
#include "perfect_cnf.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "zhegalkin.h"
#include "carnaugh_map.h"

bf_representation::perfect_conjunctuve_normal_form::perfect_conjunctuve_normal_form( std::vector<std::vector<bool>> const &m, uint dim ) :
  base(m.size() != 0 ? m[0].size() : dim, "PCNF"), matrix(m) {}

void bf_representation::perfect_conjunctuve_normal_form::convert( base &b ) const {
  if (b.getSpecificator() == "TT")
     convertToTruthTable((truth_table &)b);
  else if (b.getSpecificator() == "PDNF")
    convertToPDNF((pdnf &)b);
  else if (b.getSpecificator() == "RDNF") {
    pdnf p;
    convertToPDNF(p);
    p.convert((rdnf &)b);
  }
  else if (b.getSpecificator() == "Z") {
    truth_table t;
    convertToTruthTable(t);
    t.convert((zhegalkin &)b);
  }
  else if (b.getSpecificator() == "C")
    convertToCarnaughMap((carnaugh_map &)b);
}

void bf_representation::perfect_conjunctuve_normal_form::convertToPDNF( pdnf &p ) const {
  p = pdnf(matrix, dimension);
}

void bf_representation::perfect_conjunctuve_normal_form::output( std::ostream &os ) const {
  os << matrix;
}

bool bf_representation::perfect_conjunctuve_normal_form::eval(std::vector<bool> const &argument ) const {
  bool res = true;

  if (argument.size() != dimension)
    throw "PCNF::eval : bad argument";

  for (auto &&sign : matrix) {
    bool localRes = false;

    for (uint i = 0; i < dimension; i++)
      localRes |= bool_pow(!argument[i], sign[i]);

    res &= localRes;
  }

  return !res;
}

void bf_representation::perfect_conjunctuve_normal_form::convertToCarnaughMap( carnaugh_map &cMap ) const {
  std::vector<std::vector<bool>> map(1 << (dimension / 2));

  for (auto &x : map)
    x = std::vector<bool>(1 << ((dimension + 1) / 2), false);

  for (auto &x : matrix) {
    std::vector<bool>
      argX((dimension + 1) / 2),
      argY(dimension / 2);

    for (uint i = 0; i < (dimension + 1) / 2; i++)
      argX[i] = x[i + dimension / 2];

    for (uint i = 0; i < dimension / 2; i++)
      argY[i] = x[i];

    map[base::grayEncode(base::binaryDecode(argY))][base::grayEncode(base::binaryDecode(argX))] = true;
  }

  cMap = carnaugh_map(map, dimension);
}
