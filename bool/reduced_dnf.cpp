#include "reduced_dnf.h"

bf_representation::reduced_disjunctuve_normal_form::reduced_disjunctuve_normal_form( std::vector<std::vector<bool>> const &m ) :
  perfect_disjunctive_normal_form(m) {
  specificator = "RDNF";
}
