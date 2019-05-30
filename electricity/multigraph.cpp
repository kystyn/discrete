#include <algorithm>
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

multigraph::multigraph( mth::sparse_matrix<float> const &&IncidenceMatr ) :
    IncidenceMatr(IncidenceMatr) {}

std::vector<std::pair<uint, edge *>> multigraph::getEdgesList( void ) const {
    std::vector<std::pair<uint, edge *>> Edges(IncidenceMatr.getW());

    for (uint i = 0; i < IncidenceMatr.getH(); i++)
        for (uint j = 0; j < IncidenceMatr.getW(); j++) {
            auto w = IncidenceMatr(i, j);
            if (w < 0) {
                Edges[j].first = j;
                Edges[j].second->Vertex1 = j;
            }
            else if (w > 0) {
                Edges[j].first = j;
                Edges[j].second->Vertex2 = j;
            }
        }

    return Edges;
}

std::vector<std::pair<uint, edge *>> multigraph::findLoop( void ) const {
    std::vector<std::pair<uint, edge *>> Path;
    findLoopRec(0, Path);
    return Path;
}

void multigraph::findLoopRec( uint CurVertex, std::vector<std::pair<uint, edge *>> &Path ) const {
    auto checkLoop = [Path, CurVertex]( void ) -> bool {
        return Path.front().second->Vertex1 == CurVertex || Path.front().second->Vertex2 == CurVertex;
    };

    if (checkLoop())
        return;

    for (uint e = 0; e < IncidenceMatr.getW(); e++)
        for (uint nextVertex = 0; nextVertex < IncidenceMatr.getH(); nextVertex++)
            if (IncidenceMatr(e, nextVertex) != 0) {
                if (std::find(Path.begin(), Path.end(), [CurVertex, nextVertex]( edge * const &E ) -> bool {
                              return (E->Vertex1 == CurVertex && E->Vertex2 == nextVertex) ||
                                     (E->Vertex2 == CurVertex && E->Vertex1 == nextVertex);
                    }) != Path.end()) {
                      auto p = std::make_pair<>(e, new edge(CurVertex, nextVertex, IncidenceMatr(e, nextVertex)));
                      Path.push_back(p);
                    findLoopRec(nextVertex, Path);
                }
            }
}

multigraph multigraph::buildMinimalSpanningTree( void ) const {
    mth::sparse_matrix<float> minTreeMatr(IncidenceMatr.getH(), IncidenceMatr.getW());

    auto Edges = std::move(getEdgesList());
    std::vector<edge *> chords;
    std::sort(Edges.begin(), Edges.end(),
        []( std::pair<uint, edge> const &V1, std::pair<uint, edge> const &V2) {
          return V1.second < V2.second;
    });

    for (auto &x : Edges) {

    }
}

multigraph::multigraph() {

}
