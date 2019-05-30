#include <functional>
#include "utils.h"
#include "combNumbers.h"
#include "myuint.h"

const uint myuint32::MaxInt = 0xFFFFFFFF;

void dualstakhov( std::function<myuint32( unsigned int, unsigned int )> f, char letter ) {
    auto N = 5;
    std::cout << letter << std::endl;

//    for (auto i = 0; i <= N; i++)
//        std::cout << "     " << i;
//    std::cout << std::endl;

    for (auto i = 0; i <= N; i++) {
        std::cout << i << "     ";
        for (auto j = 0; j <= N; j++)
            std::cout << f(i, j) << "      ";
        std::cout << std::endl;
    }
}

void unarstakhov( std::function<myuint32( unsigned int )> f, char letter ) {
    auto N = 5;
    std::cout << letter << std::endl;

//    for (auto i = 0; i <= N; i++)
//        std::cout << i << "     ";
//    std::cout << std::endl;
    for (auto j = 0; j <= N; j++)
        std::cout << f(j) << "      ";
    std::cout << std::endl;
}

void stakhov( void ) {

    dualstakhov(combNumbers::A, 'A');
    unarstakhov(combNumbers::B, 'B');
    dualstakhov(combNumbers::C, 'C');
    unarstakhov(combNumbers::P, 'P');
    dualstakhov(combNumbers::U, 'S');
    dualstakhov(combNumbers::S, 'S');
}

int main( void ) {

    combNumbers::C(12,5);
  //testAll();
  //menu();
  //stakhov();

  return 0;
}
