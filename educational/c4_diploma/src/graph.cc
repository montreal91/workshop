
#include "graph.h"

Graph::Graph(size_t n) :
_adjacency_matrix()
{
  this->InitEdgelessGraph(n);
}

float Graph::GetEdge(size_t i, size_t j) const {
  return _adjacency_matrix[i][j];
}

size_t Graph::GetSize() const {
  return _adjacency_matrix.size();
}

void Graph::InitEdgelessGraph(size_t n) {
  _adjacency_matrix.clear();
  for (auto i=0; i<n; i++) {
    _adjacency_matrix.push_back(std::vector<float>());
    for (auto j=0; j<n; j++) {
      _adjacency_matrix[i].push_back(0.0f);
    }
  }
}

void Graph::SetEdge(size_t i, size_t j, float value) {
  if (j > _adjacency_matrix.size() || i > _adjacency_matrix.size()) {
    throw std::invalid_argument("Trying to set edge value outside of the graph.");
  }

  _adjacency_matrix[i][j] = value;
  _adjacency_matrix[j][i] = value;
}
