#pragma once
#include <iostream>
#include <fstream>
#include "combNumbers.h"

class tester {
private:
  combNumbers N;

  template<char Type, int MLimit, int TestCnt = 0>
  void testF( std::ostream &f ) {

    for (unsigned int m = 2; m <= MLimit; m = TestCnt != 0 ? int(pow(MLimit, 1.0f / (TestCnt + 1e-6)) * m) : m + 1) {
      unsigned int left = 0, right = m;
      bool isValuable = true;

      unsigned int n;
      for (n = 0; right - left > 1 && n <= m;) {
        try {
          switch (Type) {
          case 'A':
            N.A(m, n);
            break;
          case 'C':
            N.C(m, n);
            break;
          case 'U':
            N.U(m, n);
            break;
          case 'P':
            N.P(m);
            break;
          case 'B':
            N.B(m);
            break;
          case 'S':
            N.S(m, n);
            break;
          default:
            throw "Bad type";
          }
          left = n;
          isValuable = true;
        } catch (...) {
          isValuable = false;
          right = n;
        }

        n = (left + right) / 2;
      }
      if (n >= m - 1)
        std::cout << "for m == " << m << " all n are valuable\n";
      else {
        std::cout << Type << "(" << m << ", " << n << ")\n";
        f << m << ' ' << right << "\n";
      }
    }
  }

public:
  tester( void ) {}

  template<char numberType, int MLimit, int TestCnt = 0>
  void run( char const *fileName ) {
    std::ofstream f(fileName);
    testF<numberType, MLimit, TestCnt>(f);
  }
};