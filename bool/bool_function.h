#pragma once

#include "base.h"

/***
namespace bf_representation {

  enum class type {
  TRUTH_TABLE,
  PCNF,
  PDNF,
  RDNF,
  ZHEGALKIN
};

}
***/

class bool_function {
private:
  std::shared_ptr<bf_representation::base> representation;

  void output( std::ostream &os ) const;
  friend std::ostream & operator<<( std::ostream &os, bool_function const &bf );

public:
  bool_function( std::shared_ptr<bf_representation::base> r ) : representation(r) {}
  bool operator()( std::vector<bool> const &argument ) const;

  template<class T,
    class = typename std::enable_if<std::is_base_of<bf_representation::base, T>::value>::type>
  void convert( void ) {
    std::shared_ptr<T> repr(new T);
    ///std::shared_ptr<base> repr(new T);
    representation->convert(*repr);
    representation = repr;
  }

  std::shared_ptr<const bf_representation::base> getRepresentation( void ) const;
};

std::ostream & operator<<( std::ostream &os, bool_function const &bf );
