#include "utils.h"
#include "tester.h"

std::ostream & operator<<( std::ostream &os, myuint32 const &A ) {
  os << A.number;
  return os;
}

void menu( void ) {
  combNumbers N;
  char c;

  while (true) {
    std::cout << "A - Placements without repeat\nB - Bell\nC - Combinations\n" <<
      "P - Permutations\nU - Placements with repeat\nS - Stirling\nQ - exit\n";
  std::cin >> c;

    if (c == 'Q')
      break;

    unsigned int m, n;

    std::cout << "Enter \'m\': ";
    std::cin >> m;

    try {
      switch (c) {
      case 'A':
        std::cout << "Enter \'n\': ";
        std::cin >> n;
        std::cout << "A(" << m << ", " << n << ") = " << N.A(m, n) << "\n";
        break;
      case 'B':
        std::cout << "B(" << ") = " << N.B(m) << "\n";
        break;
      case 'C':
        std::cout << "Enter \'n\': ";
        std::cin >> n;
        std::cout << "C(" << m << ", " << n << ") = " << N.C(m, n) << "\n";
        break;
      case 'P':
        std::cout << "P(" << m << ") = " << N.P(m) << "\n";
        break;
      case 'U':
        std::cout << "Enter \'n\': ";
        std::cin >> n;
        std::cout << "U(" << m << ", " << n << ") = " << N.U(m, n) << "\n";
        break;
      case 'S':
        std::cout << "Enter \'n\': ";
        std::cin >> n;
        std::cout << "S(" << m << ", " << n << ") = " << N.S(m, n) << "\n";
        break;
      default:
        std::cout << c << " is a wrong key\n";
        std:: cin >> c;
      }
    } catch (const char *str) {
      std::cout << "Exception thrown: " << str << "\n";
    }
  }
}

void testAll( void ) {
  tester t;

  std::cout << "A\n";
  t.run<'A', 2500, 8>("limitsA.out");

  std::cout << "U\n";
  t.run<'U', 2500, 8>("limitsU.out");

  std::cout << "P\n";
  t.run<'P', 20>("limitsP.out");

  std::cout << "C\n";
  t.run<'C', 2500, 8>("limitsC.out");

  std::cout << "B\n";
  t.run<'B', 20>("limitsB.out");

  std::cout << "S\n";
  t.run<'S', 200>("limitsS.out");

}
