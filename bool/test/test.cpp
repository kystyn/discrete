#include "gtest/gtest.h"

#include "bool_function.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"
#include "truth_table.h"

using namespace bf_representation;

bool operator==( std::vector<bool> const &v1, std::vector<bool> const &v2 ) {
  if (v1.size() != v2.size())
    return false;

  for (uint i = 0; i < v1.size(); i++)
    if (v1[i] != v2[i])
      return false;

  return true;
}

const uint dim = 8;
const std::vector<bool> default_tt(1 << dim, true);
const bool_function default_bf(std::shared_ptr<truth_table>(new truth_table(default_tt)));

TEST(TT, OUTPUT) {
  auto bf = default_bf;

  std::cout << bf << std::endl;
}


TEST(PDNF, TT__PDNF) {
  auto bf = default_bf;

  std::vector<bool> tt;

  bf.convert<perfect_disjunctuve_normal_form>();

  for (uint i = 0; i < (1 << dim); i++)
    tt.push_back(bf(base::binaryEncode(i, dim)));

  std::cout << bf << std::endl;

  ASSERT_TRUE(tt == default_tt);
}

TEST(PDNF, Output) {
  auto bf = default_bf;
  bf.convert<perfect_disjunctuve_normal_form>();
  std::cout << bf << std::endl;
}

TEST(RDNF, TT__RDNF_Output) {
  auto bf = default_bf;

  std::vector<bool> tt;

  bf.convert<reduced_disjunctuve_normal_form>();

  for (uint i = 0; i < (1 << dim); i++)
    tt.push_back(bf(base::binaryEncode(i, dim)));

  ASSERT_TRUE(tt == default_tt);
  std::cout << bf << std::endl;
}

int main( int argc, char *argv[] ) {
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}