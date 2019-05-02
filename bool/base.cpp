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

uint bf_representation::base::grayDecode( uint gray ) {
  unsigned int bin;
    for (bin = 0; gray; gray >>= 1) {
      bin ^= gray;
    }
    return bin;
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

  return os;
}

std::istream & bf_representation::operator>>( std::istream &is, std::vector<bool> &v ) {
  for (auto &x : v) {
    bool q;
    is >> q;
    x = q;
  }

  return is;
}

std::vector<bool> bf_representation::operator*( std::vector<bool> const &v1, bool v2 ){
  auto v = v1;
  for (auto &x : v)
    x = x & v2;

  return v;
}

std::vector<bool> bf_representation::operator*( std::vector<bool> const &v1, std::vector<bool> const &v2 ) {
  std::vector<bool> arg1 = v1.size() > v2.size() ? v1 : v2, arg2 = v1.size() > v2.size() ? v2 : v1;
  std::vector<bool> res = arg1 * arg2[0];

  for (uint i = 1; i < arg2.size(); i++) {
    if (arg2[i]) {
      for (uint k = 0, n = res.size(); k < i + arg1.size() - n; k++)
        res.push_back(false);

      bool add = false;
      for (uint k = i; k < i + arg1.size(); k++) {
        bool prev = res[k];
        res[k] = res[k] ^ arg1[k - i] ^ add;
        add =
          (prev & add) |
          (prev & arg1[k - i]) |
          (arg1[k - i] & add);
      }
      if (add)
        res.push_back(true);
    }
  }
  return res;
}

