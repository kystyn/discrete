#include <iostream>
#include "bool_function.h"
#include "truth_table.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"

using namespace bf_representation;

int main( void ) {
  try {
    bool_function bf(std::shared_ptr<truth_table>(new truth_table({0, 1, 1, 1})));

  } catch (char const *str) {
    std::cerr << "exception thrown: " << str << std::endl;
  }

  return 0;
}