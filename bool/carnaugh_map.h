#pragma once

#include "base.h"

#include "perfect_cnf.h"
#include "perfect_dnf.h"

namespace bf_representation {
  class carnaugh_map : public base {
  public:
    carnaugh_map( std::vector<std::vector<bool>> const &m = {}, uint dim = 0 );

    bool eval( std::vector<bool> const &arg ) const override final;
    void input( std::istream &os ) override final;
    void output( std::ostream &os ) const override final;
    void convert( bf_representation::base &b ) const;
  private:
    std::vector<std::vector<bool>> map;

    template<class T, class = 
      typename std::enable_if<std::is_same<T, pdnf>::value || std::is_same<T, pcnf>::value>::type>
    void convertToPerfectNF( T &p ) const {
      std::vector<std::vector<bool>> matrix;
     
      for (uint y = 0; y < (1 << (dimension / 2)); y++)
        for (uint x = 0; x < (1 << (dimension + 1) / 2); x++)
          if (map[y][x]) {
            auto
              binX = base::binaryEncode(base::grayEncode(x)),
              binY = base::binaryEncode(base::grayEncode(y));
     
            for (auto x : binX)
              binY.push_back(x);
     
            matrix.push_back(binX);
          }

      p = T(matrix, dimension);
    }
  };
}
