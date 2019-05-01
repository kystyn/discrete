#include "base.h"
#include "truth_table.h"

void bf_representation::base::convertToTruthTable( bf_representation::truth_table &b ) const {
  std::vector<bool> tt(1 << dimension);

  for (uint i = 0; i < (1 << dimension); i++)
    tt[i] = eval(base::binaryEncode(i, dimension));

  b = tt;
}

std::string bf_representation::base::getSpecificator( void ) const { 
  return specificator;
}

uint bf_representation::base::grayEncode( uint binary ) {
  return binary ^ (binary >> 1);
}

bool bf_representation::base::bool_pow( bool x, bool y ) {
  return x == y;
}

// LITTLE-ENDIAN (Least Significant Bit First)
std::vector<bool> bf_representation::base::binaryEncode( uint dec, uint encodedSize ) {
  std::vector<bool> bin;

  do {
    bin.push_back(dec & 1);
    dec >>= 1;
  } while (dec != 0);

  while (bin.size() < encodedSize)
    bin.push_back(false);

  return bin;
}

void bf_representation::base::genNextBinary(std::vector<bool> &bin ) {
  bool add = true;

  for (uint i = 0; i< bin.size() && add; i++) {
    bin[i] = bin[i] ^ add;
    add = !bin[i];
  }
}

uint bf_representation::base::binaryDecode( std::vector<bool> const &bin ) {
  uint dec = 0;

  for (uint i = 0; i < bin.size(); i++)
    dec ^= (bin[i] << i);

  return dec;
}

std::ostream & bf_representation::operator<<( std::ostream &os, std::vector<std::vector<bool>> const &v ) {
  for (auto y : v) {
    for (auto x : y)
      std::cout << x << ' ';
    std::cout << '\n';
  }

  return os;
}

std::ostream & bf_representation::operator<<( std::ostream &os, std::vector<bool> const &v ) {
  for (auto x : v)
    std::cout << x << ' ';
  std::cout << std::endl;

  return os;
}

