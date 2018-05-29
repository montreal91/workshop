
#include "graph.h"

Graph::Graph(size_t n) :
_adjacency_matrix()
{
  this->InitEdgelessGraph(n);
}

Graph::EdgeGravity Graph::GetEdge(size_t i, size_t j) const {
  return _adjacency_matrix[i][j];
}

size_t Graph::GetSize() const {
  return _adjacency_matrix.size();
}

void Graph::InitEdgelessGraph(size_t n) {
  _adjacency_matrix.clear();
  for (auto i=0; i<n; i++) {
    _adjacency_matrix.push_back(std::vector<EdgeGravity>());
    for (auto j=0; j<n; j++) {
      _adjacency_matrix[i].push_back(EdgeGravity::repulsion);
    }
  }
}

void Graph::SetEdge(size_t i, size_t j, Graph::EdgeGravity type) {
  if (j >= _adjacency_matrix.size() || i >= _adjacency_matrix.size()) {
    throw std::invalid_argument("Trying to set edge type outside of the graph.");
  }

  _adjacency_matrix[i][j] = type;
  _adjacency_matrix[j][i] = type;
}
