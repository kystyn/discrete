#include "gtest/gtest.h"

#include "bool_function.h"
#include "perfect_dnf.h"
#include "perfect_cnf.h"
#include "reduced_dnf.h"
#include "truth_table.h"
#include "zhegalkin.h"
#include "carnaugh_map.h"

#include "properties_checker.h"

using namespace bf_representation;

std::vector<bool> genFunction( uint N, uint dim ) {
  auto table = base::binaryEncode(192 + N, 8);
  for (uint i = 2; i <= 1 << (dim - 3); i <<= 1)
    table = table * table;

  for (; table.size() < 1 << dim;)
    table.push_back(false);

  return table;
}

bool operator==( std::vector<bool> const &v1, std::vector<bool> const &v2 ) {
  if (v1.size() != v2.size())
    return false;

  for (uint i = 0; i < v1.size(); i++)
    if (v1[i] != v2[i])
      return false;

  return true;
}

const uint dim = 10;
//const std::vector<bool> default_tt(1 << dim, true);
const std::vector<bool> default_tt = genFunction(6, dim);
/*const std::vector<bool> default_tt({1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1});*/
const bool_function default_bf(std::shared_ptr<truth_table>(new truth_table(default_tt)));

TEST(TT, Eval) {
  auto bf = default_bf;

  for (uint i = 0; i < (1 << dim); i++)
    ASSERT_TRUE(default_tt[i] == bf(base::binaryEncode(i, dim)));
}

TEST(TT, TT__PDNF) {
  auto bf = default_bf;

  bf.convert<perfect_disjunctuve_normal_form>();
  ///std::cout << bf;
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(TT, TT__PCNF) {
  auto bf = default_bf;

  bf.convert<perfect_conjunctuve_normal_form>();
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(TT, TT__RDNF) {
  auto bf = default_bf;

  bf.convert<reduced_disjunctuve_normal_form>();
  ///std::cout << bf;
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}


TEST(PDNF, PDNF__PCNF) {
  auto bf = default_bf;

  bf.convert<perfect_disjunctuve_normal_form>();
  bf.convert<perfect_conjunctuve_normal_form>();
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(PDNF, PDNF_Carnaugh) {
  auto bf = default_bf;

  bf.convert<perfect_disjunctuve_normal_form>();
  bf.convert<carnaugh_map>();
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(PCNF, PCNF__PDNF) {
  auto bf = default_bf;

  bf.convert<perfect_conjunctuve_normal_form>();
  bf.convert<perfect_disjunctuve_normal_form>();
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(PCNF, PCNF_Carnaugh) {
  auto bf = default_bf;

  bf.convert<perfect_conjunctuve_normal_form>();
  bf.convert<carnaugh_map>();
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(Zhegalkin, Eval) {
  std::vector<bool> zheg = {1, 1, 0, 0, 0, 0, 1, 0};
  std::vector<bool> truthT = {1, 0, 1, 0, 1, 0, 0, 1};
  bool_function bf(std::shared_ptr<zhegalkin>(new zhegalkin(zheg)));

  for (uint i = 0; i < (1 << 3); i++)
    ASSERT_TRUE(truthT[i] == bf(base::binaryEncode(i, 3)));
}

TEST(TT, TT__Zhegalkin) {
  bool_function bf = default_bf;
  bf.convert<zhegalkin>();
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(TT, TT_Carnaugh) {
  bool_function bf = default_bf;
  bf.convert<carnaugh_map>();
  ///std::cout << bf;
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(Zhegalkin, Zhegalkin_Carnaugh) {
  bool_function bf = default_bf;
  bf.convert<zhegalkin>();
  bf.convert<carnaugh_map>();
  bf.convert<zhegalkin>();
  bf.convert<truth_table>();

  auto ptr = bf.getRepresentation().get();

  ASSERT_TRUE(((const truth_table *)ptr)->getTable() == default_tt);
}

TEST(Gray, codes_full) {
  uint count = 4;
  auto prev = base::binaryEncode(base::grayEncode(0), count);
  for (uint i = 1; i < (1 << count); i++) {
    auto cur = base::binaryEncode(base::grayEncode(i), count);
    uint dist = 0;

    for (uint k = 0; k < count; k++)
      dist += cur[k] & !prev[k] | !cur[k] & prev[k];
    ASSERT_EQ(dist, 1);
    prev = cur;
  }
}

TEST(BoolMultiply, 1) {
  ASSERT_TRUE(base::binaryDecode(base::binaryEncode(198) * base::binaryEncode(198)) == 198 * 198);
  uint n = 128;

  for (uint i = 0; i <= n; i++)
    for (uint j = i; j <= n; j++) {
      ASSERT_TRUE(base::binaryDecode(base::binaryEncode(i) * base::binaryEncode(j)) == i * j);
    }
}

TEST(Checker, ZeroPreserve) {
  bool_function bf(std::shared_ptr<truth_table>(new truth_table({0, 0, 1, 1})));
  properties_checker chk(bf);
  ASSERT_TRUE(chk.checkZeroPreserve());

  bf = bool_function(std::shared_ptr<truth_table>(new truth_table({1, 0, 1, 1})));
  chk = properties_checker(bf);
  ASSERT_FALSE(chk.checkZeroPreserve());
}

TEST(Checker, OnePreserve) {
  bool_function bf(std::shared_ptr<truth_table>(new truth_table({0, 0, 1, 0})));
  properties_checker chk(bf);
  ASSERT_FALSE(chk.checkOnePreserve());

  bf = bool_function(std::shared_ptr<truth_table>(new truth_table({1, 0, 1, 1})));
  chk = properties_checker(bf);
  ASSERT_TRUE(chk.checkOnePreserve());
}

TEST(Checker, Linear) {
  bool_function bf(std::shared_ptr<zhegalkin>(new zhegalkin({1, 1, 1, 0, 0, 0, 0, 0})));
  properties_checker chk(bf);
  ASSERT_TRUE(chk.checkLinear());

  bf = bool_function(std::shared_ptr<zhegalkin>(new zhegalkin({1, 0, 1, 1, 1, 0, 0, 0})));
  chk = properties_checker(bf);
  ASSERT_FALSE(chk.checkLinear());
}

TEST(Checker, SelfDuality) {
  bool_function bf(std::shared_ptr<truth_table>(new truth_table({1, 0, 1, 0, 1, 0, 1, 0})));
  properties_checker chk(bf);
  ASSERT_TRUE(chk.checkSelfDuality());

  bf = bool_function(std::shared_ptr<truth_table>(new truth_table({1, 0, 0, 0, 1, 0, 1, 0})));
  chk = properties_checker(bf);
  ASSERT_FALSE(chk.checkSelfDuality());
}

TEST(Checker, Monotone) {
  bool_function bf(std::shared_ptr<truth_table>(new truth_table({1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0})));
  properties_checker chk(bf);
  ASSERT_FALSE(chk.checkMonotone());

  bf = bool_function(std::shared_ptr<truth_table>(new truth_table({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1})));
  chk = properties_checker(bf);
  ASSERT_TRUE(chk.checkMonotone());
}

int main( int argc, char *argv[] ) {
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}