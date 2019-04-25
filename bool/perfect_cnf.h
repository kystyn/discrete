#pragma once

#include "base.h"

namespace bf_representation {
class perfect_conjunctuve_normal_form : public base {
public:
  perfect_conjunctuve_normal_form( std::vector<std::vector<bool>> const &m = {}, uint dim = 0 );
  bool eval(std::vector<bool> const &argument ) const final;
  void convert( base &b ) const;
  void output( std::ostream &os ) const;
private:
  std::vector<std::vector<bool>> matrix;

  void convertToPDNF( pdnf &p ) const;
};
}
