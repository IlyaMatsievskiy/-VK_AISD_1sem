#include <iostream>
#include "IGraph.h"
#include "ListGraph.hpp"
#include <stack>
#include <random>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <limits>
using namespace std;

//возвращает порядок вершин(городов) - решение задачи коммивояжера по мст
vector<int> trav(const vector<vector<pair<float, int>>>& mst, int start = 0) {
    vector<bool> visited(mst.size(), false);
    vector<int> path;
    
    stack<int> s;
    s.push(start);
    
    while (!s.empty()) {
        auto cur = s.top();
        s.pop();
        if (!visited[cur]) {
            path.push_back(cur);
            visited[cur] = true;
            for (auto i : mst[cur]) {
                if (!visited[i.second]) {
                    s.push(i.second);
                }
            }
        }
    }
    return path;
}

//подсчет дистанции между двумя точками
float dist(pair<int, int> point1, pair<int, int> point2) {
    float x = point1.first - point2.first;
    float y = point1.second - point2.second;
    return sqrt(x * x + y * y);
}

//подсчет длины пути из решения задачи коммивояжера по мст
int trav_len(const vector<int>& path, const vector<pair<int, int>>& points) {
    float length = 0.0;
    
    for (int i = 0; i < points.size() - 1; ++i) {
        length += dist(points[path[i]], points[path[i + 1]]);
    }
    
    length += dist(points[path.back()], points[path[0]]); //путь в начальный пункт
    return length;
}

//генерация нормально распределенных точек
vector<pair<int, int>> genPoints(int n) {
    vector<pair<int, int>> points;
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d{0,100};

    for (int i = 0; i < n; ++i) {
        points.emplace_back(d(gen), d(gen));
    }
    return points;
}

//поиск длины пути коммивояжера по очередной перестановке и по матрице дистанций
float permutDist(const vector<int>& permutation, const vector<vector<float>>& dists) {
    float length = 0.0;
    for (int i = 0; i < permutation.size() - 1; ++i) {
        length += dists[permutation[i]][permutation[i + 1]];
    }
    
    length += dists[permutation.back()][permutation.front()]; //путь в начальный пункт
    return length;
}

//поиск оптимального решения задачи коммивояжера с помощью перебора
float minDist(const vector<vector<float>>& dists) {
    vector<int> vertices(dists.size());
    
    for (int i = 0; i < dists.size(); ++i) {
        vertices[i] = i;
    }
    float minLen = permutDist(vertices, dists);
    
    while (next_permutation(vertices.begin(), vertices.end())) {
        minLen = min(minLen, permutDist(vertices, dists));
    }
    return minLen;
}

//вычисление среднеквадратичное отклонение
float deviation(const vector<float>& q_i, float m) {
    float variance = 0.0;
    for (float q : q_i) {
        variance += pow((q - m), 2);
    }
    return sqrt(variance / q_i.size());
}

void solution() {
    int k = 30; //число запусков
    for (int n = 2; n < 20; ++n) {
        cout << n << " вершин:" << endl;
        vector<float> q_i; //отношения приближённого решения к точному
        for (int i = 0; i < k; ++i) {
            ListGraph graph(n);
            auto points = genPoints(n);
            vector<vector<float>> dists(n, vector<float>(n, 0.0));
            
            for (int i = 0; i < points.size(); ++i) {
                for (int j = i + 1; j < points.size(); ++j) {
                    float d = dist(points[i], points[j]);
                    graph.AddEdge(i, j, d);
                    dists[i][j] = d;
                    dists[j][i] = d;
                }
            }
            
            auto mst = graph.GetMST();
            auto path = trav(mst);
            
            q_i.push_back(trav_len(path, points) / minDist(dists));
        }
        float m = (accumulate(q_i.begin(), q_i.end(), 0.0)) / k; //среднее
        float d_q = deviation(q_i, m); //среднеквадратичное отклонение
        
        cout << "Среднее значение " << m << endl;
        cout << "Среднеквадратичное отклонение " << d_q << endl;
    }
}
    
int main() {
    solution();
    return 0;
}
    
//    for (int i = 0; i < m; ++i) {
//        int b, e, w;
//        cin >> b >> e >> w;
//        graph.AddEdge(b - 1, e - 1, w);
//    }
    
//    auto mst = graph.GetMST();
//    
//    cout << "Длина мст: ";
//    cout << graph.GetMSTWeight() << endl;
//    
//    auto path = trav(mst);
//    
//    cout << "Приближенное решение: ";
//    cout << trav_len(path, points) << endl;
//    
//    cout << "Точное решение: ";
//    cout << minDist(dists) << endl;

