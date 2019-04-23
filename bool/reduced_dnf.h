#pragma once

#include "base.h"
#include "perfect_dnf.h"

namespace bf_representation {

class reduced_disjunctuve_normal_form : public base {
public:
  reduced_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m = {} );

  bool eval(std::vector<bool> const &argument ) const final;
  void output( std::ostream &os ) const final;

private:
  std::vector<std::vector<bool>> matrix;
};
}
