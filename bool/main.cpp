#include <iostream>
#include <fstream>

#include "truth_table.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "perfect_cnf.h"
#include "zhegalkin.h"
#include "carnaugh_map.h"

#include "properties_checker.h"

using namespace bf_representation;

bool_function genFunction( uint N, uint dim ) {
  auto table = base::binaryEncode(192 + N, 8);
  for (uint i = 2; i <= 1 << (dim - 3); i <<= 1)
    table = table * table;

  for (; table.size() < 1 << dim;)
    table.push_back(false);

  return std::shared_ptr<truth_table>(new truth_table(table));
}

int main( void ) {
  try {
    uint N = 6, dim = 8;
    auto bf = genFunction(N, dim);

    std::ofstream ofs("bf.txt");

    // truth table
    ofs << "Truth table\n" << bf;
    // pdnf
    bf.convert<perfect_disjunctuve_normal_form>();
    ofs << "PDNF\n" << bf;
    // rdnf
    bf.convert<reduced_disjunctuve_normal_form>();
    ofs << "RDNF\n" << bf;
    // pcnf
    bf.convert<perfect_conjunctuve_normal_form>();
    ofs << "PCNF\n" << bf;
    // zhegalkin
    bf.convert<zhegalkin>();
    ofs << "Zhegalkin polynom\n" << bf;
    // carnaugh
    bf.convert<carnaugh_map>();
    ofs << "Carnaugh map\n" << bf;

    properties_checker chk(bf);

    ofs = std::ofstream("properties.txt");

    ofs << (chk.checkZeroPreserve() ? "Zero is preserved\n" : "Zero is not preserved\n");
    ofs << (chk.checkOnePreserve() ? "One is preserved\n" : "One is not preserved\n");
    ofs << (chk.checkMonotone() ? "Is monotone\n" : "Is not monotone\n");
    ofs << (chk.checkLinear() ? "Is linear\n" : "Is not linear\n");
    ofs << (chk.checkSymmetric() ? "Is symmetric\n" : "Is not symmetric\n");

  } catch (char const *str) {
    std::cerr << "exception thrown: " << str << std::endl;
  }

  return 0;
}