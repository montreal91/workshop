
#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

//
// A class to incapsulate all graph-related logic.
//
class Graph {
public:
  typedef std::unique_ptr<Graph> Ptr_t;

  //
  // Creates edgeless graph with n vertexes.
  //
  explicit Graph(size_t n);

  //
  // Returns value of an edge that connects i'th and j'th vertexes.
  //
  float GetEdge(size_t i, size_t j) const;

  //
  // Returns number of vertices in current graph.
  //
  size_t GetSize() const;

  //
  // Deletes all edges and sets number of vertexes to n
  //
  void InitEdgelessGraph(size_t n);

  //
  // Sets value of an edge that connects i'th and j'th vertexes to n.
  //
  void SetEdge(size_t i, size_t j, float val);

private:
  typedef std::vector<std::vector<float>> Matrix_t;

  Matrix_t _adjacency_matrix;
};
