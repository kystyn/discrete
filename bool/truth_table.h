#pragma once

#include "base.h"

namespace bf_representation {

class truth_table : public base {
public:
  truth_table( std::vector<bool> const &truthTable = {} );

  bool eval(std::vector<bool> const &argument ) const override final;
  void input( std::istream &os ) override final;
  void output( std::ostream &os ) const override final;

  void convert( base & ) const override;

  std::vector<bool> const & getTable( void ) const;
private:
  std::vector<bool> truthTable;

  void convertToPDNF( pdnf & ) const;
  void convertToPCNF( pcnf & ) const;
  void convertToRDNF( rdnf & ) const;
  void convertToZhegalkin( zhegalkin & ) const;
  void convertToCarnaughMap( carnaugh_map & ) const;
};

}
