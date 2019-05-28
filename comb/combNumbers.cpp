#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath>
#include "combNumbers.h"

std::vector<myuint32> combNumbers::genStirlingString( uint m, uint n ) {
    std::vector<myuint32> stirling(n + 1, 0);

    if (n == 0 && m == 0)
        return {1};

    stirling[0] = 0;
    for (unsigned int i = 1; i <= m; i++) {
        if (i < n + 1)
            stirling[i] = 1;
        myuint32
            left = stirling[0],
            whereToWrite = stirling[0];

        for (unsigned int j = 1; j <= std::min(i - 1, n); j++) {
            whereToWrite = stirling[j];
            stirling[j] = left + stirling[j] * j;
            left = whereToWrite;
        }
    }

    return stirling;
}

myuint32 combNumbers::B( unsigned int n ) {
    myuint32 r = 0;
    auto s = genStirlingString(n, n);

    for (auto &el : s)
        r += el;

    return r;
}

myuint32 combNumbers::S( unsigned int m, unsigned int n ) {
  if (m < n)
    return 0;
  return genStirlingString(m, n).back();
}

myuint32 combNumbers::C( unsigned int m, unsigned int n ) {
  if (m < n)
    return 0;

  if (n > m / 2)  // C(m, n) == C(m, m - n)
    n = m - n;

  std::vector<myuint32> comb(n + 1, 0);
  comb[0] = 1;

  for (unsigned int i = 1; i <= m; i++) {
    unsigned int
        prevs = std::min(i + 1, n + 1),
        s = prevs;

    myuint32
        left = comb[0],
        whereToWrite = comb[0],
        prevlast = comb[prevs - 1];
    for (int j = std::max<int>(1, (int)s - (int)n); j < s; j++) {

      whereToWrite = comb[j];
      comb[j] += left;
      left = whereToWrite;
    }

    comb[s - 1] += prevlast * 2 * (i % 2 == 0);
  }

  return comb[n];
}

myuint32 combNumbers::U( unsigned int m, unsigned int n ) {

  if (m == 0 && n == 0)
    return 1;

  int 
    b, t = int(log2(n));
  myuint32 y = 1, M = myuint32(m);

  for (int i = 0; i < t + 1; i++) {
    b = n % 2;
    n /= 2;

    if (b == 1)
      y *= M;

    M *= M;
  }

  return y;
}

myuint32 combNumbers::A( unsigned int m, unsigned int n ) {
  myuint32 p = 1;

  if (m < n)
    return 0;

  for (unsigned int i = m; i >= m - n + 1; i--)
    p *= i;
  return p;
}

myuint32 combNumbers::P( unsigned int n ) {
  return A(n, n);
}
