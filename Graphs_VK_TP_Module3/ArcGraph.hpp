#ifndef ArcGraph_hpp
#define ArcGraph_hpp

#include <stdio.h>
#include "IGraph.h"
#include <vector>
#include <cassert>

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int size);
    ArcGraph(const IGraph& graph);
    ~ArcGraph() override = default;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int verticesCount = 0;
    std::vector<std::pair<int, int>> edges;
};

#endif /* ArcGraph_hpp */
