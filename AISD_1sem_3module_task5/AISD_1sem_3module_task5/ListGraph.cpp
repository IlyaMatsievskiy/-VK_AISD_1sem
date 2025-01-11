#include "ListGraph.hpp"

ListGraph::ListGraph(int size) : adjacencyLists(size) {}


void ListGraph::AddEdge(int from, int to, float w) {
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].push_back({w, to});
    adjacencyLists[to].push_back({w, from}); //тк граф неоринтированный
}

int ListGraph::VerticesCount() const {
    return (int)adjacencyLists.size();
}

std::vector<std::pair<float, int>> ListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}


float ListGraph:: GetMSTWeight() const{
    int intMax = 0x7FFFFFFF;
    std::vector<bool> visited(VerticesCount(), false);
    std::vector<float> d(VerticesCount(), intMax); //длина кратчайшего пути из from в to
    
    d[0] = 0;
    std::set<std::pair<float, int>> q; //множество для построения остова
    q.insert({0.0, 0});
    
    while (!q.empty()) {
        std::pair<float, int> cur = *(q.begin());
        visited[cur.second] = true;
        q.erase(q.begin());
        
        for (auto next : GetNextVertices(cur.second)) {
            if (!visited[next.second] and d[next.second] > next.first) {
                q.erase({d[next.second], next.second}); //удаляем старое значение
                
                d[next.second] = next.first;
                
                q.insert({d[next.second], next.second}); //добавляем новое
            }
        }
    }
    
    float weight = 0.0;
    for (float i : d) {
        if (i != intMax)
            weight += i;
    }
    return weight;
}

std::vector<std::vector<std::pair<float, int>>> ListGraph:: GetMST() const{
    int intMax = 0x7FFFFFFF;
    std::vector<bool> visited(VerticesCount(), false);
    std::vector<int> p(VerticesCount(), -1);
    std::vector<float> d(VerticesCount(), intMax); //длина кратчайшего пути из from в to
    
    std::vector<std::vector<std::pair<float, int>>> mst(VerticesCount());
    
    d[0] = 0.0;
    p[0] = 0;
    std::set<std::pair<float, int>> q; //множество для построения остова
    q.insert({0.0, 0});
    
    while (!q.empty()) {
        std::pair<float, int> cur = *(q.begin());
        visited[cur.second] = true;
        q.erase(q.begin());
        
        
        for (auto next : GetNextVertices(cur.second)) {
            if (!visited[next.second] and d[next.second] > next.first) {
                q.erase({d[next.second], next.second}); //удаляем старое значение
                
                p[next.second] = cur.second;
                d[next.second] = next.first;
                
                q.insert({d[next.second], next.second}); //добавляем новое
            }
        }
    }
    
    for (int i = 1; i < VerticesCount(); ++i) {
        if (p[i] != -1) {
            mst[i].emplace_back(d[i], p[i]);
            mst[p[i]].emplace_back(d[i], i);
        }
    }

    return mst;
}







