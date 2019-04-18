#pragma once

#include "base.h"

namespace bf_representation {

class perfect_disjunctive_normal_form;

class truth_table : public base {
public:
  truth_table( std::vector<bool> const &truthTable = {} );

  bool eval(std::vector<bool> const &argument ) const final;
  void output( std::ostream &os ) const final;

  void convert( base & ) const;
  void convertToPDNF( pdnf & ) const;
private:
  std::vector<bool> truthTable;
};

}
