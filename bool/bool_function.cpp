#include <cmath>
#include <algorithm>
#include "bool_function.h"

std::ostream & operator<<( std::ostream &os, bool_function const &bf ) {
  bf.output(os);
  return os;
}

bool bool_function::operator()( std::vector<bool> const &argument ) const {
  return representation->eval(argument);
}

void bool_function::output( std::ostream &os ) const {
  representation->output(os);
}

std::shared_ptr<const bf_representation::base> bool_function::getRepresentation( void ) const {
  return representation;
}
