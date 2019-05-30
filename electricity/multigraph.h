#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H

#include <iostream>
#include <vector>
#include "def.h"

struct edge {
    uint
      Vertex1, Vertex2; // Vertices number
    float Weight;

    edge( uint V1, uint V2 ) : Vertex1(V1), Vertex2(V2) {}
};

class multigraph
{
public:
    multigraph();

private:
    std::vector<std::vector<int>> IncidenceMatr;
    friend std::istream & operator>>( std::istream &, multigraph & );
};

#endif // MULTIGRAPH_H
