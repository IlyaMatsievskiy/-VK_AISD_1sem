#ifndef GraphAlgorithms_hpp
#define GraphAlgorithms_hpp

#include <stdio.h>
#include "IGraph.h"
#include <functional>
#include <deque>
#include <vector>

// Обход в ширину
void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func);
void mainBFS(const IGraph& graph, const std::function<void(int)>& func);

// Обход в глубину
void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func);
void mainDFS(const IGraph& graph, const std::function<void(int)>& func);

// Топологическая сортировка
std::deque<int> topologicalSort(const IGraph& graph);

#endif /* GraphAlgorithms_hpp */
