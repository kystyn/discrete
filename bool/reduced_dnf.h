#pragma once

#include "base.h"
#include "perfect_dnf.h"

namespace bf_representation {

class reduced_disjunctuve_normal_form : public base {
public:
  reduced_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m = {}, uint dim = 0 );

  bool eval(std::vector<bool> const &argument ) const override final;
  void input( std::istream &is ) override final;
  void output( std::ostream &os ) const override final;
  void convert( base &b ) const override;

private:
  std::vector<std::vector<bool>> matrix;
};
}
