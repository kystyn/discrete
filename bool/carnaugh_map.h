#pragma once

#include "base.h"

namespace bf_representation {
  class carnaugh_map : public base {
  public:
    carnaugh_map( std::vector<std::vector<bool>> const &m );
    bool eval( std::vector<bool> const &arg ) const;
    void output( std::ostream &os ) const;
  private:
    std::vector<std::vector<bool>> map;
  };
}
