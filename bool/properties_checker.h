#pragma once

#include <map>
#include "def.h"
#include "bool_function.h"
#include "truth_table.h"
#include "zhegalkin.h"

class properties_checker {
public:
  properties_checker( bool_function const &bf ) : bf(bf) {}

  bool checkZeroPreserve( void ) {
    uint dim = bf.getRepresentation()->getDimension();
    std::vector<bool> arg(dim, false);
    return !bf(arg);
  }

  bool checkOnePreserve( void ) {
    uint dim = bf.getRepresentation()->getDimension();
    std::vector<bool> arg(dim, true);
    return bf(arg);
  }

  bool checkSelfDuality( void ) {
    uint dim = bf.getRepresentation()->getDimension();
    std::vector<bool> arg(dim, false);
    for (uint i = 0; i < (uint)(1 << dim); i++) {
      auto invArg = arg;

      for (auto &x : invArg)
        x = !x;

      if (bf(arg) != !bf(invArg))
        return false;
      bf_representation::base::genNextBinary(arg);
    }
    return true;
  }

  bool checkLinear( void ) {
    if (bf.getRepresentation()->getSpecificator() != "Z")
      bf.convert<bf_representation::zhegalkin>();
    auto coeffs = ((const bf_representation::zhegalkin *)(bf.getRepresentation().get()))->getCoeffs();

    auto isLinearMultiplier = []( std::vector<bool> const &arg ) -> bool {
      uint cnt = 0;
      for (auto x : arg)
        if (x)
          cnt++;

      return cnt == 0 || cnt == 1;
    };

    uint dim = bf.getRepresentation()->getDimension();
    std::vector<bool> arg(dim, false);

    for (uint i = 0; i < (uint)(1 << dim); i++)
      if (coeffs[i])
        if (!isLinearMultiplier(bf_representation::base::binaryEncode(i)))
          return false;

    return true;
  }

  bool checkMonotone( void ) {
    uint dim = bf.getRepresentation()->getDimension();
    if (bf.getRepresentation()->getSpecificator() != "TT")
      bf.convert<bf_representation::truth_table>();
    auto table = ((const bf_representation::truth_table *)(bf.getRepresentation().get()))->getTable();
    for (uint frag = 2; frag < (uint)(1 << dim); frag <<= 1)
      for (uint step = 0; step < frag - 1; step++)
        for (uint i = step * (uint)(1 << dim) / frag; i < (step + 1) * (uint)(1 << dim) / frag; i++)
          if (table[i] > table[i + (uint)(1 << dim) / frag])
            return false;

    return true;
  }

  bool checkSymmetric( void ) {
    std::map<uint, std::vector<uint>> params;

    uint dim = bf.getRepresentation()->getDimension();
    bf.convert<bf_representation::truth_table>();
    std::vector<bool> arg((uint)(1 << dim), false);
    auto table = ((const bf_representation::truth_table *)(bf.getRepresentation().get()))->getTable();

    auto getTrueCount = []( std::vector<bool> const &v ) -> uint {
      uint cnt = 0;
      for (auto x : v)
        if (x)
          cnt++;

      return cnt;
    };

    for (uint i = 0; i < (uint)(1 << dim); i++, bf_representation::base::genNextBinary(arg))
      params[getTrueCount(arg)].push_back(i);

    for (uint i = 0; i < params.size(); i++) {
      if (params[i].size() == 0)
        continue;

      bool val = table[params[i][0]];
      for (uint j = 0; j < params[i].size(); j++)
        if (val != table[params[i][j]])
          return false;
    }

    return true;
  }

private:
  bool_function bf;
};
