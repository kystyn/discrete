#pragma once

#include "base.h"

namespace bf_representation {
class zhegalkin : public base {
public:
  zhegalkin( std::vector<bool> const &coefficients = {} );

  bool eval( std::vector<bool> const &argument ) const final;
  void convert( base &b ) const;
  void output( std::ostream &os ) const;
private:
  std::vector<bool> coefficients;
};
}
