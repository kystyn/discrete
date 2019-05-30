#include "multigraph.h"

std::istream & operator>>( std::istream &is, multigraph &Graph ) {
    uint V, E; // vertices and edges count
    is >> V >> E;

    Graph.IncidenceMatr = mth::sparse_matrix<float>(V, E);


    for (uint i = 0; i < V; i++)
        for (uint j = 0; j < E; j++)
            is >> Graph.IncidenceMatr(i, j);

    return is;
}

multigraph::multigraph() {

}
