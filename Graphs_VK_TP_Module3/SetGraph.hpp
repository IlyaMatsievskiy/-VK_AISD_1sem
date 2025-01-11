#ifndef SetGraph_hpp
#define SetGraph_hpp

#include <stdio.h>
#include "IGraph.h"
#include <vector>
#include <unordered_set>
#include <cassert>

class SetGraph : public IGraph {
public:
    explicit SetGraph(int size);
    SetGraph(const IGraph& graph);
    ~SetGraph() override = default;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> adjacencySets;
};

#endif /* SetGraph_hpp */
