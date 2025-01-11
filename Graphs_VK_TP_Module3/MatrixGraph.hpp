#ifndef MatrixGraph_hpp
#define MatrixGraph_hpp

#include <stdio.h>

#include "IGraph.h"
#include <vector>
#include <cassert>

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int size);
    MatrixGraph(const IGraph& graph);
    ~MatrixGraph() override = default;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjacencyMatrix;
};

#endif /* MatrixGraph_hpp */
