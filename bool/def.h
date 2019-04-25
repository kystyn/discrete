#pragma once

using uint = unsigned int;

namespace bf_representation {
  class truth_table;
  class reduced_disjunctuve_normal_form;
  class perfect_disjunctuve_normal_form;
  class perfect_conjunctuve_normal_form;
  class zhegalkin;

  using rdnf = reduced_disjunctuve_normal_form;
  using pdnf = perfect_disjunctuve_normal_form;
  using pcnf = perfect_conjunctuve_normal_form;
}

#include <vector>
#include <set>
#include <memory>
#include <cmath>
#include <iostream>
