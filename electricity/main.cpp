#include <iostream>
#include "sparse_matrix.h"

using namespace std;

int y( mth::sparse_matrix<int> const &a ) {
    return a(0, 0);
}

int main()
{
    mth::sparse_matrix<int> a(3, 5), b(5, 4);

    for (uint i = 0; i < 3; i++)
        for (uint j = 0; j < 5; j++) {
            a(i, j) = int(3 * i + j);
        }

    for (uint i = 0; i < 5; i++)
        for (uint j = 0; j < 4; j++) {
            b(i, j) = int(5 * i + j);
        }

    a *= b;

    cout << "Hello World!" << endl;
    return 0;
}
