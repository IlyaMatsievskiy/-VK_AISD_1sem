#ifndef ListGraph_h
#define ListGraph_h

#include "IGraph.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <set>

class ListGraph : public IGraph {
public:
    explicit ListGraph(int size);
    ListGraph(const IGraph& graph);
    ~ListGraph() override = default;

    void AddEdge(int from, int to, float w) override;
    int VerticesCount() const override;
    std::vector<std::pair<float, int>> GetNextVertices(int vertex) const override;
    
    float GetMSTWeight() const override;
    
    std::vector<std::vector<std::pair<float, int>>> GetMST() const override;

private:
    std::vector<std::vector<std::pair<float, int>>> adjacencyLists;
};


#endif /* ListGraph_h */
