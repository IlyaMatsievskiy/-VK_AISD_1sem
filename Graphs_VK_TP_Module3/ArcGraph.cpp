#include "ArcGraph.hpp"

ArcGraph::ArcGraph(int size) : verticesCount(size) {}

ArcGraph::ArcGraph(const IGraph &graph) : verticesCount(graph.VerticesCount()){
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (int to : graph.GetNextVertices(from)) {
            edges.emplace_back(from, to);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(0 <= from && 0 <= to);

    //если в дальнейшем понадобится динамический граф, остальные реализации динамику не поддерживают
    int count = std::max(from, to);
    if (count >= verticesCount) {
        verticesCount = count + 1;
    }
    
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < verticesCount);
    std::vector<int> nextVertices;
    
    for (const auto& pair : edges) {
        if (pair.first == vertex) {
            nextVertices.push_back(pair.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < verticesCount);
    std::vector<int> prevVertices;
    
    for (const auto& pair : edges) {
        if (pair.second == vertex) {
            prevVertices.push_back(pair.first);
        }
    }
    return prevVertices;
}
