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

    if (arg1.size() != arg2.size())
      throw "Merge compare: bad args";

    uint arg1c = 0, arg2c = 0;

    for (uint i = 0, n = arg1.size() / 2; i < n; i++) {
      if (arg1[i] == !arg1[i + n])
        arg1c++;
      if (arg2[i] == !arg2[i + n])
        arg2c++;
    }

    if (arg1c == arg2c + 1) {
      arg1.erase(arg1.begin() + extract);
      arg1.erase(arg1.begin() + arg1.size() / 2  + extract - 1); // -1 because of previous erase
      res = 1;
    }
    else if (arg2c == arg1c + 1) {
      arg2.erase(arg2.begin() + extract);
      arg2.erase(arg2.begin() + arg1.size() / 2  + extract - 1); // -1 because of previous erase
      res = 2;
    }
    else
      return res;

    return res * compare(0, 0, arg1, arg2);
  }
};
}
