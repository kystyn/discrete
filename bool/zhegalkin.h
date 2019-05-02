#pragma once

#include "base.h"

namespace bf_representation {
class zhegalkin : public base {
public:
  zhegalkin( std::vector<bool> const &coefficients = {} );

  bool eval( std::vector<bool> const &argument ) const override final;
  void convert( base &b ) const override;
  void input( std::istream &is ) override final;
  void output( std::ostream &os ) const override final;
private:
  std::vector<bool> coefficients;
};
}
