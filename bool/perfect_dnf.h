#pragma once

#include "base.h"

namespace bf_representation {
class reduced_disjunctuve_normal_form;

class perfect_disjunctive_normal_form : public base {
public:
  perfect_disjunctive_normal_form( std::vector<std::vector<bool>> const &m = {} );

  bool eval(std::vector<bool> const &argument ) const final;
  void output( std::ostream &os ) const final;

  void convert( base &b ) const;

private:
  std::vector<std::vector<bool>> matrix;

  void convertToRDNF( bf_representation::rdnf &b ) const;

  //[0; extractBeg] U [extractEnd; dimension)
  static bool compare( uint extractBeg, uint extractEnd, 
    std::vector<bool> const &arg1, std::vector<bool> const &arg2 ) {
    if (arg1.size() != arg2.size())
      return false;
    for (uint i = 0; i < arg1.size(); i++)
      if (i <= extractBeg || extractEnd <= i)
        if (arg1[i] != arg2[i])
          return false;
    return true;
  }

  static bool compareMerge( uint extract, 
    std::vector<bool> const &arg1, std::vector<bool> const &arg2 ) {
    if (arg1.size() != arg2.size() + 1 && arg2.size() != arg1.size() + 1) {
      return false;
    }

    auto tmp = arg1;
    if (arg2.size() == arg1.size() + 1) {
      tmp = arg2;
      tmp.erase(tmp.begin() + extract);
      return compare(0, 0, arg1, tmp);
    }

    tmp = arg1;
    tmp.erase(tmp.begin() + extract);
    return compare(0, 0, arg2, tmp);
  }
};
}
