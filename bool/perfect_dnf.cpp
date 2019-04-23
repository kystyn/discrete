#include <algorithm>
#include "base.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"

/*** Perfect disjunctive normal form ***/
bf_representation::perfect_disjunctuve_normal_form::perfect_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m ) : 
    base(m.size() != 0 ? m[0].size() : 0, "PDNF"), matrix(m) {}

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

void bf_representation::perfect_disjunctuve_normal_form::output( std::ostream &os ) const {
  for (auto &&str : matrix) {
    for (auto i : str)
      os << i << ' ';
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
            m.push_back(comb);

            if (std::find(reduced.begin(), reduced.end(), i) == reduced.end())
              reduced.push_back(i);

            if (std::find(reduced.begin(), reduced.end(), j) == reduced.end())
              reduced.push_back(j);

            reducedAnything = true;

            break; // reduce just by one parameter
          }
          // merge w | (w & z) = w
          /*else if (which = compareMerge(position, m[i], m[j])) {
            if (which == 1) {
              m.push_back(m[j]);
              reduced.push_back(j);
            }
            else {
              m.push_back(m[i]);
              reduced.push_back(i);
            }
            reducedAnything = true;
          }          */


    std::sort(reduced.begin(), reduced.end());
    // remove reduced terms
    for (uint i = 0; i < reduced.size(); i++)
      m.erase(m.begin() + (reduced[i] - i));

    // remove same strings
    std::vector<std::vector<bool>>::iterator it;
    for (uint i = 0; i < m.size() - 1; i++)
      for (uint j = i + 1; j < m.size();)
        if ((it = std::find(m.begin() + j, m.end(), m[i])) != m.end())
          m.erase(it);
        else
          j++;
  } while (reducedAnything);

  r = m;
}

void bf_representation::perfect_disjunctuve_normal_form::convert( base &b ) const {
  if (b.getSpecificator() == "RDNF") {
    convertToRDNF((rdnf &)b);
  }
}
