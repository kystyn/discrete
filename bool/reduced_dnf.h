#pragma once

#include "base.h"
#include "perfect_dnf.h"

namespace bf_representation {

class reduced_disjunctuve_normal_form : public perfect_disjunctive_normal_form {
public:
  reduced_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m = {} );
};
}
