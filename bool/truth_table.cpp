#include "truth_table.h"
#include "perfect_dnf.h"
#include "reduced_dnf.h"

bf_representation::truth_table::truth_table( std::vector<bool> const &truthTable ) :
  base((uint)log2(truthTable.size()), "TT"), truthTable(truthTable) {
  if (1 << dimension != truthTable.size())
    std::cerr << "TT constructor :: bad truth table!";
}

void bf_representation::truth_table::output( std::ostream &os ) const {
  for (auto i : truthTable)
    os << i << ' ';
  os << std::endl;
}

bool bf_representation::truth_table::eval(std::vector<bool> const &argument ) const {
  if (argument.size() != dimension)
    throw "truth table :: eval : bad argument!";
  return truthTable[base::binaryDecode(argument)];
}

void bf_representation::truth_table::convert( bf_representation::base &b ) const {
  if (b.getSpecificator() == "PDNF") 
    convertToPDNF((pdnf &)b);
  else if (b.getSpecificator() == "RDNF") {
    convertToRDNF((rdnf &)b);
  }
}

void bf_representation::truth_table::convertToPDNF( pdnf &pdnf ) const {
  std::vector<std::vector<bool>> m;

  for (uint i = 0; i < (1 << dimension); i++)
    if (truthTable[i])
      m.push_back(base::binaryEncode(i, dimension));

  pdnf = m;
}

void bf_representation::truth_table::convertToRDNF( rdnf &r ) const {
  pdnf p;
  convertToPDNF(p);
  p.convert(r);
}
