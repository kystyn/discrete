#include <iostream>
#include "bool_function.h"
#include "truth_table.h"
#include "perfect_dnf.h"

using namespace bf_representation;

int main( void ) {
  try {
    bool_function bf(std::shared_ptr<truth_table>(new truth_table({0, 1, 1, 0, 1, 0, 0, 1})));

    for (uint i = 0; i < 8; i++)
      std::cout << bf(base::binaryEncode(i, 3)) << ' ';
    std::cout << std::endl;
    bf.convert<bf_representation::perfect_disjunctive_normal_form>();

    std::cout << bf(base::binaryEncode(5, 3)) << std::endl;
    std::cout << bf;

  } catch (char const *str) {
    std::cerr << "exception thrown: " << str << std::endl;
  }

  return 0;
}