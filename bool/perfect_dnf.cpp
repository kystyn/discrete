#include "base.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"

/*** Perfect disjunctive normal form ***/
bf_representation::perfect_disjunctive_normal_form::perfect_disjunctive_normal_form( std::vector<std::vector<bool>> const &m ) : 
    base(m.size() != 0 ? m[0].size() : 0, "PDNF"), matrix(m) {}

bool bf_representation::perfect_disjunctive_normal_form::eval(std::vector<bool> const &argument ) const {
  bool res = false;

  if (argument.size() != dimension)
    throw "PDNF::eval : bad argument";

  for (auto &&sign : matrix) {
    bool localRes = false;

    for (uint i = 0; i < dimension; i++)
      localRes &= bool_pow(argument[i], sign[i]);

    res |= localRes;
  }

  return res;
}

void bf_representation::perfect_disjunctive_normal_form::output( std::ostream &os ) const {
  for (auto &&str : matrix) {
    for (auto i : str)
      os << i << ' ';
    os << "\n";
  }
}

void bf_representation::perfect_disjunctive_normal_form::convertToRDNF( rdnf &r ) const {
  std::vector<std::vector<bool>> m = matrix;
  bool reducedAnything;

  do {
    std::vector<bool> reduced(m.size(), false);
    reducedAnything = false;

    for (uint i = 0; i < m.size(); i++)
      for (uint j = 0; j < m.size(); j++)
        for (uint position = 0; position < m[0].size(); position++)
          // convolution w & x | w & ~x == w
          if (i != j && compare(position, position + 1, m[i], m[j]) && m[i][position] != m[j][position]) {
            std::vector<bool> comb = m[i];
            comb.erase(comb.begin() + position);
            m.push_back(comb);
            reduced[i] = reduced[j] = true;
            reducedAnything = true;
          }
          else if (i != j && compareMerge(position, m[i], m[j])) {
            if (m[i].size() > m[j].size())
              m.push_back(m[j]);
            else
              m.push_back(m[i]);
            reduced[i] = reduced[j] = true;
            reducedAnything = true;
          }


    // remove reduced terms
    for (uint i = 0; i < reduced.size(); i++)
      if (reduced[i])
        m.erase(m.begin() + i);
  } while (reducedAnything);

  r = m;
}

void bf_representation::perfect_disjunctive_normal_form::convert( base &b ) const {
  if (b.getSpecificator() == "RDNF") {
    convertToRDNF((rdnf &)b);
  }
}
