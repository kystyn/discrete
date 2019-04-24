#pragma once

#include "base.h"

namespace bf_representation {

class perfect_disjunctuve_normal_form : public base {
public:
  perfect_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m = {} );

  bool eval(std::vector<bool> const &argument ) const final;
  void output( std::ostream &os ) const final;

  void convert( base &b ) const;

private:
  std::vector<std::vector<bool>> matrix;

  void convertToRDNF( bf_representation::rdnf &b ) const;

  //[0; extractBeg) U [extractEnd; dimension)
  static bool compare( uint extractBeg, uint extractEnd, 
    std::vector<bool> const &arg1, std::vector<bool> const &arg2 ) {
    if (arg1.size() != arg2.size())
      return false;
    for (uint i = 0; i < arg1.size(); i++)
      if ((extractBeg > i || i >= extractEnd) && (extractBeg + arg1.size() / 2 > i || i >= extractEnd + arg1.size() / 2))
        if (arg1[i] != arg2[i])
          return false;
    return true;
  }

  static uint compareMerge( uint extract, 
    std::vector<bool> arg1, std::vector<bool> arg2 ) {

    uint res = 0;
    uint found = 0;

    if (arg1.size() != arg2.size())
      throw "Merge compare: bad args";

    for (uint i = 0, n = arg1.size(); i < n; i++)
      if (arg1[i] != arg2[i]) {
        found++;
        res = i;
      }

    if (res > arg1.size() / 2)
      res -= arg1.size() / 2;

    if (found == 1 && res == extract)
      if (arg2[res] == 0) // no elem in arg2
        return 1;
      else
        return 2;
    return 0;
  }
};
}
