#pragma once

#include "base.h"

namespace bf_representation {
class perfect_conjunctuve_normal_form : public base {
public:
  perfect_conjunctuve_normal_form( std::vector<std::vector<bool>> const &m = {}, uint dim = 0 );
  bool eval(std::vector<bool> const &argument ) const override final;
  void convert( base &b ) const override;
  void input( std::istream &is ) override final;
  void output( std::ostream &os ) const override final;
private:
  std::vector<std::vector<bool>> matrix;

  void convertToPDNF( pdnf & ) const;
  void convertToCarnaughMap( carnaugh_map & ) const;
};
}
