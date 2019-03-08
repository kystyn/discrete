#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include "combNumbers.h"


int heavyside( int x ) {
  return x >= 0;
}

void combNumbers::genStirling2Table( std::vector<std::vector<myuint32>> &table, unsigned int m, unsigned int n ) {
  table.resize(m + 1);

  for (unsigned int i = 0; i <= m; i++) {
    table[i] = std::vector<myuint32>(i + 1);
    table[i][0] = 0;
    table[i][i] = 1;
  }
  table[0][0] = 0;

  for (unsigned int i = 2; i <= m; i++)
    for (unsigned int j = 1, s = (unsigned int)table[i].size(); j < s - 1; j++)
      table[i][j] = table[i - 1][j - 1] + table[i - 1][j] * j;
}

myuint32 combNumbers::B( unsigned int n ) {
  std::vector<std::vector<myuint32>> stirling;
  genStirling2Table(stirling, n, n);

  myuint32 s = 0;
  for (unsigned int i = 0; i <= n; i++)
    s += stirling[n][i];

  return s;
}

myuint32 combNumbers::S( unsigned int m, unsigned int n ) {
  if (m < n)
    return 0;

  std::vector<std::vector<myuint32>> stirling;
  genStirling2Table(stirling, m, n);
  return stirling[m][n];
}

myuint32 combNumbers::C( unsigned int m, unsigned int n ) {
  if (m < n)
    return 0;

  if (n > m / 2)  // C(m, n) == C(m, m - n)
    n = m - n;

  std::vector<std::vector<myuint32>> comb(m + 1);

  for (unsigned int i = 0; i <= m; i++) {
    comb[i] = std::vector<myuint32>(std::min((i + 2) / 2, n + 1)); // i + 2 == (i + 1) + 1
    comb[i][0] = 1;
  }

  for (unsigned int i = 1; i <= m; i++)
    for (unsigned int  j = 1, s = (unsigned int)comb[i].size(); j < s; j++)
      comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j + heavyside(j - (unsigned int)comb[i - 1].size()) * (i - 1 - j * 2)];     // C(i - 1, j) == C(i - 1, i - 1 - j)

  return comb[m][n];
}

myuint32 combNumbers::U( unsigned int m, unsigned int n ) {

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
