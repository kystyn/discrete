#include "multigraph.h"

std::istream & operator>>( std::istream &is, multigraph &Graph ) {
    uint V, E; // vertices and edges count
    is >> V >> E;

    Graph.IncidenceMatr.resize(V);

    for (auto &x : Graph.IncidenceMatr)
        x.resize(E);

    Graph.Edges.resize(E);

    for (uint i = 0; i < V; i++)
        for (uint j = 0; j < E; j++) {
            is >> Graph.IncidenceMatr[i][j];
            Graph.Edges[j].Weight = Graph.IncidenceMatr[i][j];
            if (Graph.IncidenceMatr[i][j] < 0)
                Graph.Edges[j].Vertex1 = j;
            else if (Graph.IncidenceMatr[i][j] > 0)
                Graph.Edges[j].Vertex2 = j;
        }

    return is;
}

multigraph::multigraph() {

}
