#pragma once

#include "base.h"

namespace bf_representation {
class perfect_conjuctive_normal_form : public base {
public:
  perfect_conjuctive_normal_form( std::vector<std::vector<bool>> const &m = {} );
  bool eval(std::vector<bool> const &argument ) const final;
private:
  std::vector<std::vector<bool>> matrix;
};
}
