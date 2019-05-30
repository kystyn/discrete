#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H

#include <iostream>
#include <vector>
#include "sparse_matrix.h"
#include "def.h"

struct edge {
    uint
      Vertex1, Vertex2; // Vertices number
    float Weight;

    bool operator<( edge const &E2 ) const {
        return Weight < E2.Weight;
    }

    edge( uint V1, uint V2, float Weight ) : Vertex1(V1), Vertex2(V2), Weight(Weight) {}
};

class multigraph
{
public:
    multigraph();

    multigraph( mth::sparse_matrix<float> const &&IncidenceMatr );

    multigraph buildMinimalSpanningTree( void ) const;
    // if one loop or more, returns first found
    std::vector<std::pair<uint, edge *>> findLoop( void ) const;

private:
    void findLoopRec( uint CurVertex, std::vector<std::pair<uint, edge *>> &Path ) const;

    std::vector<std::pair<uint, edge *>> getEdgesList( void ) const;

    mth::sparse_matrix<float> IncidenceMatr;
    friend std::istream & operator>>( std::istream &, multigraph & );
};

#endif // MULTIGRAPH_H
