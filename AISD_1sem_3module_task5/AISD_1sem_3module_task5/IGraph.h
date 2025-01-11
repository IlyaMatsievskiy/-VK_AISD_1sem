#ifndef IGraph_h
#define IGraph_h

#include <vector>

struct IGraph {
    virtual ~IGraph() {}
        
    virtual void AddEdge(int from, int to, float w) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<std::pair<float, int>> GetNextVertices(int vertex) const = 0;
    
    virtual float GetMSTWeight() const = 0;
    
    virtual std::vector<std::vector<std::pair<float, int>>> GetMST() const = 0;
};

#endif /* IGraph_h */
