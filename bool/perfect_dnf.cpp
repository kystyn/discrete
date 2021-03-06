#include <algorithm>
#include "base.h"
#include "truth_table.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "perfect_cnf.h"
#include "zhegalkin.h"
#include "carnaugh_map.h"

/*** Perfect disjunctive normal form ***/
bf_representation::perfect_disjunctuve_normal_form::perfect_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m, uint dim ) : 
    base(m.size() != 0 ? m[0].size() : dim, "PDNF"), matrix(m) {}

bool bf_representation::perfect_disjunctuve_normal_form::eval(std::vector<bool> const &argument ) const {
  bool res = false;

  if (matrix.size() == 0)
    return false;

  if (argument.size() != dimension)
    throw "PDNF::eval : bad argument";

  for (auto sign : matrix) {
    bool localRes = true;

    for (uint i = 0; i < dimension; i++)
      localRes &= bool_pow(argument[i], sign[i]);

    res |= localRes;
  }

  return res;
}

void bf_representation::perfect_disjunctuve_normal_form::input( std::istream &is ) {
  is >> dimension;
  bool q;
  while (is >> q) {
    std::vector<bool> sign(dimension);
    sign[0] = q;

    for (uint i = 1; i < dimension; i++) {
      is >> q;
      sign[i] = q;
    }
  }
}

void bf_representation::perfect_disjunctuve_normal_form::output( std::ostream &os ) const {
  if (matrix.size() == 0)
    os << "false\n";

  for (uint i = 0, n = matrix.size(); i < n; i++) {
    os << ' ';
    for (uint j = 0; j < dimension - 1; j++)
      os << (matrix[i][j] ? "x" : "!x") << j << " & ";
    os << (matrix[i][dimension - 1] ? "x" : "!x") << dimension - 1;

    if (i != n - 1)
      os << "\nV\n";
    else
      os << "\n";
  }
}

void bf_representation::perfect_disjunctuve_normal_form::convertToRDNF( rdnf &r ) const {
  std::vector<std::vector<bool>> m = matrix;

  for (auto &str : m)
    for (uint i = 0, n = str.size(); i < n; i++)
      str.push_back(!str[i]);

  bool reducedAnything;
  uint which;

  do {
    std::vector<uint> reduced;
    reducedAnything = false;

    for (uint i = 0, n = m.size(); i < n; i++)
      if (reduced.size() < n)
        for (uint j = i + 1; j < n; j++)
          for (uint position = 0; position < dimension; position++)
            // convolution w & x | w & ~x == w
            if (compare(position, position + 1, m[i], m[j]) && // && i != j
                  m[i][position] == !m[j][position] &&              // if position in 'i' is equal to NOT position in 'j'
                  m[i][position] == !m[i][position + dimension] &&  // if position exists in i and j (next str)
                  m[j][position] == !m[j][position + dimension]) {

              std::vector<bool> comb = m[i];
              comb[position] = false;
              comb[position + dimension] = false;
              if (std::find(m.begin() + n, m.end(), comb) == m.end())
                m.push_back(comb);

              if (std::find(reduced.begin(), reduced.end(), i) == reduced.end())
                reduced.push_back(i);

              if (std::find(reduced.begin(), reduced.end(), j) == reduced.end())
                reduced.push_back(j);

              reducedAnything = true;

              break; // reduce just by one parameter
            }
            // merge w | (w & z) = w
            else if (which = compareMerge(position, m[i], m[j])) {
              if (which == 1) {
                if (std::find(reduced.begin(), reduced.end(), i) == reduced.end())
                  reduced.push_back(i);
              }
              else {
                if (std::find(reduced.begin(), reduced.end(), j) == reduced.end())
                  reduced.push_back(j);
              }
              reducedAnything = true;
            }


    std::sort(reduced.begin(), reduced.end());
    // remove reduced terms
    for (uint i = 0; i < reduced.size(); i++)
      m.erase(m.begin() + (reduced[i] - i));

    // remove same strings
    ///std::vector<std::vector<bool>>::iterator it;
    ///for (int i = 0, n = m.size() - 1; i < n; i++)
    ///  for (int j = i + 1; j < m.size();)
    ///    if ((it = std::find(m.begin() + j, m.end(), m[i])) != m.end())
    ///      m.erase(it);
    ///    else
    ///      j++;
  } while (reducedAnything);

  r = rdnf(m, dimension);
}

void bf_representation::perfect_disjunctuve_normal_form::convertToPCNF( bf_representation::pcnf &b ) const {
  b = pcnf(matrix, dimension);
}

void bf_representation::perfect_disjunctuve_normal_form::convert( base &b ) const {
  if (b.getSpecificator() == "RDNF")
    convertToRDNF((rdnf &)b);
  else if (b.getSpecificator() == "TT")
     convertToTruthTable((truth_table &)b);
  else if (b.getSpecificator() == "Z") {
     truth_table t;
     convertToTruthTable(t);
     t.convert((zhegalkin &)b);
  }
  else if (b.getSpecificator() == "C")
    convertToCarnaughMap((carnaugh_map &)b);
  else if (b.getSpecificator() == "PCNF")
    convertToPCNF((pcnf &)b);
}

void bf_representation::perfect_disjunctuve_normal_form::convertToCarnaughMap( carnaugh_map &cMap ) const {
  std::vector<std::vector<bool>> map((uint)(1 << (dimension / 2)));

  for (auto &x : map)
    x = std::vector<bool>((uint)(1 << ((dimension + 1) / 2)), false);

  for (auto &x : matrix) {
    std::vector<bool>
      argX((dimension + 1) / 2),
      argY(dimension / 2);

    for (uint i = 0; i < (dimension + 1) / 2; i++)
      argX[i] = x[i + dimension / 2];

    for (uint i = 0; i < dimension / 2; i++)
      argY[i] = x[i];

    map[base::grayDecode(base::binaryDecode(argY))][base::grayDecode(base::binaryDecode(argX))] = true;
  }

  cMap = carnaugh_map(map, dimension);
}
