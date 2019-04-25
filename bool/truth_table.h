#pragma once

#include "base.h"

namespace bf_representation {

class truth_table : public base {
public:
  truth_table( std::vector<bool> const &truthTable = {} );

  bool eval(std::vector<bool> const &argument ) const final;
  void output( std::ostream &os ) const final;

  void convert( base & ) const;

  std::vector<bool> const & getTable( void ) const;
private:
  std::vector<bool> truthTable;

  void convertToPDNF( pdnf & ) const;
  void convertToPCNF( pcnf & ) const;
  void convertToRDNF( rdnf & ) const;
  void convertToZhegalkin( zhegalkin & ) const;
};

}
