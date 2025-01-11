/*2. Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).*/

//#include <iostream>
//#include <cassert>
//#include <vector>
//#include <queue>
//#include <functional>
//
//struct IGraph {
//    virtual ~IGraph() {}
//        
//    virtual void AddEdge(int from, int to) = 0;
//
//    virtual int VerticesCount() const  = 0;
//
//    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
//    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
//};
//
//class ListGraph : public IGraph {
//public:
//    explicit ListGraph(int size);
//    ListGraph(const IGraph& graph);
//    ~ListGraph() override = default;
//
//    void AddEdge(int from, int to) override;
//    int VerticesCount() const override;
//    std::vector<int> GetNextVertices(int vertex) const override;
//    std::vector<int> GetPrevVertices(int vertex) const override;
//
//private:
//    std::vector<std::vector<int>> adjacencyLists;
//};
//
//ListGraph::ListGraph(int size) : adjacencyLists(size) {}
//
//ListGraph::ListGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()) {
//    for (int i = 0; i < graph.VerticesCount(); ++i) {
//        adjacencyLists[i] = graph.GetNextVertices(i);
//    }
//}
//
//void ListGraph::AddEdge(int from, int to) {
//    assert(0 <= from && from < adjacencyLists.size());
//    assert(0 <= to && to < adjacencyLists.size());
//    adjacencyLists[from].push_back(to);
//}
//
//int ListGraph::VerticesCount() const {
//    return (int)adjacencyLists.size();
//}
//
//std::vector<int> ListGraph::GetNextVertices(int vertex) const {
//    assert(0 <= vertex && vertex < adjacencyLists.size());
//    return adjacencyLists[vertex];
//}
//
//std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
//    assert(0 <= vertex && vertex < adjacencyLists.size());
//    std::vector<int> prevVertices;
//    
//    for (int from = 0; from < adjacencyLists.size(); ++from) {
//        for (int to: adjacencyLists[from]) {
//            if (to == vertex)
//                prevVertices.push_back(from);
//        }
//    }
//    return prevVertices;
//}
//
//void BFS(const IGraph &graph, int vertex, std::vector<int> &d, std::vector<int> &k)
//{
//    std::queue<int> qu;
//    qu.push(vertex);
//    
//    d[vertex] = 0;
//    k[vertex] = 1;
//    
//    
//    while (!qu.empty()) {
//        int current = qu.front();
//        qu.pop();
//        
//        for (int next : graph.GetNextVertices(current)) {
//            if (d[next] == 0x7FFFFFFF) {
//                qu.push(next);
//            }
//            if (d[current] + 1 < d[next]) {
//                d[next] = d[current] + 1;
//                k[next] = k[current];
//            } 
//            else if (d[next] == d[current] + 1) {
//                k[next] += k[current];
//            }
//        }
//    }
//}
//
//
//int main() {
//    int v, n;
//    std::cin >> v >> n;
//    ListGraph graph(v);
//    int el1, el2;
//    
//    for (size_t i = 0; i < n; ++i) {
//        std::cin >> el1 >> el2;
//        graph.AddEdge(el1, el2);
//        graph.AddEdge(el2, el1);
//    }
//    
//    std::cin >> el1 >> el2;
//    
//    std::vector<int> d(v, 0x7FFFFFFF); //кратчайшие расстояния от исходной до i-ой
//    std::vector<int> k(v, 0); //число кратчайших путей от исходной до i-ой
//    
//    BFS(graph, el1, d, k);
//    
//    std::cout << k[el2] << std::endl;
//}

/*3. Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.
 
 Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.*/

//#include <iostream>
//#include <cassert>
//#include <vector>
//#include <set>
//
//using namespace std;
//
//
//void printGraph(const vector<vector<pair<int, int>>>& graph) {
//    cout << "Graph adjacency list:" << endl;
//    for (size_t u = 0; u < graph.size(); ++u) {
//        cout << "Vertex " << u << ":";
//        for (const auto& edge : graph[u]) {
//            cout << " -> (" << edge.first << ", " << edge.second << ")";
//        }
//        cout << endl;
//    }
//}
//
//// Функция для вывода вектора расстояний
//void printDistances(const vector<int>& d) {
//    cout << "Distances from source:" << endl;
//    for (size_t i = 0; i < d.size(); ++i) {
//        if (d[i] == 20000) {
//            cout << "Vertex " << i << ": INF" << endl;
//        } else {
//            cout << "Vertex " << i << ": " << d[i] << endl;
//        }
//    }
//}
//
//// Функция для вывода вектора предков
//void printPredecessors(const vector<int>& p) {
//    cout << "Predecessors:" << endl;
//    for (size_t i = 0; i < p.size(); ++i) {
//        cout << "Vertex " << i << ": " << p[i] << endl;
//    }
//}
//
//// Функция для вывода множества
//void printQueue(const set<pair<int, int>>& q) {
//    cout << "Priority queue (set):" << endl;
//    for (const auto& [dist, vertex] : q) {
//        cout << "(" << dist << ", " << vertex << ") ";
//    }
//    cout << endl;
//}
//
//
//bool Relax(vector<int> &d, vector<int> &p, int u, int v, int w) {
//    if (d[v] > d[u] + w) {
//        d[v] = d[u] + w;
//        p[v] = u;
//        return true;
//    }
//    return false;
//}
//
//void Dijkstra(vector<vector<pair<int, int>>> graph, set<pair<int, int>> &q, vector<int> &d, vector<int> &p, int to, int intMax) {
//    while (!q.empty()) {
//        
//        pair<int, int> edge = *(q.begin());
//        q.erase(q.begin());
//        int u = edge.second;
//        
//        for (auto [v, w] : graph[u]) {
//            if (d[v] == intMax) {
//                d[v] = d[u] + w;
//                p[v] = u;
//                q.insert({d[v], v});
//            }
//            
//            else if (Relax(d, p, u, v, w)){
//                //заменяем на более оптимальный путь
//                q.erase({w, v});
//                q.insert({d[v], v});
//            }
//        }
//    }
//}
//
//
//int main() {
//    int n, m, u, v, w, from, to;
//    
//    cin >> n; //количество городов
//    cin >> m; //количество дорог
//    
//    vector<vector<pair<int, int>>> graph(n);
//    
//    bool edgeInclude = false;
//    for (int i = 0; i < m; ++i) {
//        cin >> u >> v >> w;
//        
//        for (auto &edge : graph[u]) {
//            if (edge.first == v) {
//                edgeInclude = true;
//                edge.second = min(edge.second, w);
//            }
//        }
//        
//        if (!edgeInclude) {
//            graph[u].emplace_back(v, w);
//        }
//        
//        edgeInclude = false;
//        for (auto &edge : graph[v]) {
//            if (edge.first == u) {
//                edgeInclude = true;
//                edge.second = min(edge.second, w);
//            }
//        }
//        
//        if (!edgeInclude) {
//            graph[v].emplace_back(u, w);
//        }
//        
//        edgeInclude = false;
//    }
//    
//    printGraph(graph);
//    
//    
//    
//    
//    cin >> from >> to;
//    
//    int intMax = 0x7FFFFFFF; //можно вынести в глобальную переменную, но вроде как запрещено((
//    vector<int> d(n, intMax); //длина кратчайшего пути из from в to
//    vector<int> p(n, -1);  //вершина, через которую идет кратчайший путь из from в to
//    
//    set<pair<int, int>> q; //множетсво для алгоритма
//    d[from] = 0;
//    q.insert({0, from});
//    
//    // Вывод структур
//    printGraph(graph);
//    printDistances(d);
//    printPredecessors(p);
//    printQueue(q);
//    
//    Dijkstra(graph, q, d, p, to, intMax);
//    
//    cout << d[to] << endl;
//    
//    return 0;
//}

/*5. Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду: [ 1 2 3 4 ] [ 5 6 7 8 ] [ 9 10 11 12] [ 13 14 15 0 ], где 0 задает пустую ячейку. Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.*/

//Это решение так и не заработало, скорее всего проблемы в функции move и getnext, также надо добавить очистку для множества q

//#include <array>
//#include <iostream>
//#include <map>
//#include <set>
//#include <vector>
//#include <assert.h>
//
//static const size_t LINE_SIZE = 4;
//static const size_t FIELD_SIZE = LINE_SIZE * LINE_SIZE;
//
//using FieldArray = std::array<uint8_t, FIELD_SIZE>; // uint8_t a[FIELD_SIZE];
//
//const FieldArray EMPTY_STATE = {
//    0, 0, 0,0,
//    0, 0, 0,0,
//    0, 0, 0,0,
//    0, 0, 0,0
//};
//
//const FieldArray GOAL_STATE = {
//    1,2,3,4,
//    5,6,7,8,
//    9,10,11,12,
//    13,14,15,0
//};
//
//class FieldState {
//public:
//    FieldState(const FieldArray &a) : zero_pos(0) {
//        for (int i = 0; i < a.size(); ++i) {
//            arr[i] = a[i];
//            if (arr[i] == 0) {
//                zero_pos = i;
//            }
//        }
//    }
//
//    FieldState(const FieldState &a) : arr(a.arr), zero_pos(a.zero_pos) {
//    }
//    
//    std::vector<FieldState> GetNextVertices(std::string& path) const {
//        std::vector<FieldState> result;
//        if (zero_pos % LINE_SIZE != 0) { // right
//            FieldState st(*this);
//            st.moveRight();
//            result.push_back(st);
//            path += "R";
//        }
//        if (zero_pos % LINE_SIZE != (LINE_SIZE - 1)) { // left
//            FieldState st(*this);
//            st.moveLeft();
//            result.push_back(st);
//            path += "L";
//        }
//        if (zero_pos >= LINE_SIZE) { // down
//            FieldState st(*this);
//            st.moveDown();
//            result.push_back(st);
//            path += "D";
//        }
//        if (zero_pos < LINE_SIZE * (LINE_SIZE - 1)) { // up
//            FieldState st(*this);
//            st.moveUp();
//            result.push_back(st);
//            path += "U";
//        }
//        return result;
//    }
//
//    bool operator==(const FieldState& r) const {
//        return arr == r.arr;
//    }
//
//    bool operator<(const FieldState& r) const {
//        return arr < r.arr;
//    }
//
//    void print() const {
//        std::cout << std::endl << "--------" << std::endl;
//        for (int i = 0; i < arr.size(); ++i) {
//            if (i % LINE_SIZE == 0) {
//                std::cout << std::endl;
//            }
//            std::cout << (int)arr[i] << " ";
//        }
//    }
//    
//    bool isEven() const {
//        int n = 0;
//        //кол-во инверсий
//        for (int i = 0; i < arr.size(); ++i) {
//            for (int j = 0; j < i; ++j) {
//                if (arr[j] > arr[i]) ++n;
//            }
//        }
//        
//        //номер строки с пустой клеткой
//        size_t k = zero_pos + 1;
//        
//        if ((n + k) % 2 == 0) return true;
//        
//        return false;
//    }
//    
//    int heuristic() const{
//        int h = 0;
//        for (int i = 0; i < arr.size(); ++i) {
//            int row = i / LINE_SIZE;
//            int col = i % LINE_SIZE;
//            if (arr[i] == 0) {
//                int goal_row = (FIELD_SIZE - 1) / LINE_SIZE;
//                int goal_col = LINE_SIZE - 1;
//                h += std::abs(row - goal_row) + std::abs(col - goal_col);
//                continue;
//            }
//            int goal_row = (arr[i] - 1) / LINE_SIZE;
//            int goal_col = (arr[i] - 1) % LINE_SIZE;
//            h += std::abs(row - goal_row) + std::abs(col - goal_col);
//        }
//        return h;
//    }
//    
//    void Print() const {
//            for (size_t i = 0; i < FIELD_SIZE; ++i) {
//                if (i % LINE_SIZE == 0) {
//                    std::cout << "\n";
//                }
//                std::cout << (int)arr[i] << " ";
//            }
//            std::cout << "\n";
//        }
//
//    const FieldArray& GetArray() const {
//        return arr;
//    }
//    
//
//private:
//    void moveDown() {
//        size_t new_zero_pos = zero_pos - LINE_SIZE;
//        std::swap(arr[zero_pos], arr[new_zero_pos]);
//        zero_pos = new_zero_pos;
//    }
//
//    void moveUp() {
//        size_t new_zero_pos = zero_pos + LINE_SIZE;
//        std::swap(arr[zero_pos], arr[new_zero_pos]);
//        zero_pos = new_zero_pos;
//    }
//
//    void moveLeft() {
//        size_t new_zero_pos = zero_pos + 1;
//        std::swap(arr[zero_pos], arr[new_zero_pos]);
//        zero_pos = new_zero_pos;
//    }
//
//    void moveRight() {
//        size_t new_zero_pos = zero_pos - 1;
//        std::swap(arr[zero_pos], arr[new_zero_pos]);
//        zero_pos = new_zero_pos;
//    }
//
//    FieldArray arr;
//    size_t zero_pos;
//    friend struct FieldStateHasher;
//};
//
//struct FieldStateHasher
//{
//public:
//    size_t operator()(const FieldState &state) const
//    {
//        size_t hash = 0;
//        std::memcpy(&hash, state.arr.data(), sizeof(hash));
//        return hash;
//    }
//};
//
//
////void aStar(const FieldState& start) {
////    FieldState goal_state(GOAL_STATE);
////    FieldState empty_state(EMPTY_STATE);
////
////    std::map<FieldState, FieldState> parents;
////    std::map<FieldState, int> score;
////    std::map<FieldState, int> score_no_h;
////    std::set<std::pair<int, FieldState>> q;
////
////    parents.insert({start, empty_state});
////    score.insert({start, start.heuristic()});
////    score_no_h.insert({start, 0});
////    q.insert({start.heuristic(), start});
////    
////
////    FieldState cur_state(EMPTY_STATE);
////    bool found = false;
////    while (!q.empty()) {
////        std::pair<int, FieldState> edge = *(q.begin());
////        q.erase(q.begin());
////        cur_state = edge.second;
////
////        if (cur_state == goal_state) {
////            found = true;
////            break;
////        }
////
////        for (auto& child : cur_state.GetNextVertices()) {
////            auto it = parents.find(child);
////            
////            if (child == goal_state) {
////                cur_state = child;
////                found = true;
////                break;
////            }
////            
//////            child.print();
//////            std::cout << child.heuristic() << std::endl;
////            if (it == parents.end()) {
////                parents.insert({child, cur_state});
////                score.insert({child, child.heuristic()});
////                score_no_h.insert({child, score_no_h[cur_state] + 1});
////                q.insert({score[child], child});
////            }
////            
//////            else if (score[child] > score_no_h[cur_state] + child.heuristic()) {
//////                int dist_old = score[child];
//////                score_no_h[child] = score_no_h[cur_state] + 1;
//////                score[child] = score_no_h[child] + child.heuristic();
//////                it->second = cur_state;
////////                parents.insert({child, cur_state});
//////                q.erase({dist_old, child});
//////                q.insert({score[child], child});
//////            }
////
////        }
////    }
////    
////    if (q.size() > 9000) {
////        int averageEvristika = (q.begin()->first + q.rbegin()->first) / 2;
////        q.erase(q.upper_bound(std::make_pair(averageEvristika, cur_state)), q.end());
////    }
////
////    if (found) {
////        int steps_count = 0;
////        while (cur_state != empty_state) {
////            steps_count++;
////            cur_state.print();
////            auto it = parents.find(cur_state);
////            assert(it != parents.end());
////            cur_state = it->second;
////        }
////        std::cout << "Solution found. steps_count=" << steps_count << std::endl;
////    } else {
////        std::cout << "Solution not found. vertices_count=" << parents.size() << std::endl;
////    }
////}
//
//
//std::string aStar(const FieldState& start) {
//    FieldState goal_state(GOAL_STATE);
//    
//    if (!start.isEven())
//            return "-1";
//        
//    std::unordered_map<FieldState, char, FieldStateHasher> visited;
//    visited[start] = 'S';
//        
//    std::set<std::pair<int, FieldState>> q;
//    q.insert({start.heuristic(), start});
//    
//    FieldState cur_state(EMPTY_STATE);
//    while (true) {
//        std::pair<int, FieldState> edge = *(q.begin());
//        q.erase(q.begin());
//        cur_state = edge.second;
//        int cur_state_len = edge.first;
//        
//        if (cur_state == goal_state)
//            break;
//        
//        std::string path_vert = "";
//        
//        int count = 0;
//        for (auto& child : cur_state.GetNextVertices(path_vert)) {
//            if (visited.find(child) == visited.end()) {
//                visited[child] = path_vert[count];
//                q.insert({cur_state_len + child.heuristic() + 1, child});
//            }
//            count++;
//        }
//    }
//    
//    std::string path;
//    
//    while (visited[goal_state] != 'S')
//    {
//        char move = visited[goal_state];
//        
//        std::vector<FieldState> child;
//        std::string now_path = "";
//        
//        child = goal_state.GetNextVertices(now_path);
//        
//        switch (move)
//        {
//            case 'L':
//            {
//                goal_state = child[now_path.find("R")];
//                path += 'L';
//                break;
//            }
//            case 'R':
//            {
//                goal_state = child[now_path.find("L")];
//                path += 'R';
//                break;
//            }
//            case 'D':
//            {
//                goal_state = child[now_path.find("U")];
//                path += 'D';
//                break;
//            }
//            case 'U':
//            {
//                goal_state = child[now_path.find("D")];
//                path += 'U';
//                break;
//            }
//        }
//    }
//    
//    std::reverse(path.begin(), path.end());
//    return path;
//}
//    
//
//int main() {
////    FieldState st({1, 0, 3, 4,
////                   5, 2, 6, 8,
////                   9, 10, 7, 12,
////                   13, 14, 11, 15});
////    std::cout << "Heuristic: " << test_state.heuristic() << std::endl;
//    
//    FieldArray arr;
//    
//    for (size_t i = 0; i < FIELD_SIZE; ++i) {
//        int val;
//        std::cin >> val;
//        arr[i] = static_cast<uint8_t>(val);
//    }
//
//    FieldState st(arr);
//    
//    std::string solution = aStar(st);
//    std::cout << solution.size() << '\n' << solution << std::endl;
//    return 0;
//}


/*5. Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду: [ 1 2 3 4 ] [ 5 6 7 8 ] [ 9 10 11 12] [ 13 14 15 0 ], где 0 задает пустую ячейку. Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.*/


//#include <iostream>
//#include <array>
//#include <cassert>
//#include <unordered_map>
//#include <queue>
//#include <algorithm>
//#include <set>
//#include <cstring>
//
//const char FieldSize = 16;
//const size_t LineSize = 4;
//const int k = 6;
//const int max_q = 2000;
//const std::array<char, FieldSize> finishField = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
//
//
//class GameState
//{
//public:
//    GameState(const std::array<char, FieldSize> &field)
//    : field(field)
//    {
//        emptyPos = -1;
//        for (int i = 0; i < FieldSize; i++)
//        {
//            if (field[i] == 0)
//            {
//                emptyPos = i;
//            }
//        }
//        assert(emptyPos != -1);
//    }
//    
//    bool IsComplete() const
//    {
//        return field == finishField;
//    }
//    
//    bool IsSolvable() const
//    {
//        return !((getInvCount() + emptyPos / LineSize + 1) % 2);
//    }
//    
//    bool CanMoveLeft() const
//    {
//        return emptyPos % LineSize != LineSize - 1;
//    }
//    
//    bool CanMoveRight() const
//    {
//        return emptyPos % LineSize != 0;
//    }
//    
//    bool CanMoveUp() const
//    {
//        return emptyPos < LineSize * (LineSize - 1);
//    }
//    
//    bool CanMoveDown() const
//    {
//        return emptyPos > LineSize - 1;
//    }
//    
//    GameState MoveLeft() const
//    {
//        assert(CanMoveLeft());
//        
//        GameState newState(*this);
//        std::swap(newState.field[emptyPos], newState.field[emptyPos + 1]);
//        newState.emptyPos++;
//        return newState;
//    }
//    
//    GameState MoveRight() const
//    {
//        assert(CanMoveRight());
//        
//        GameState newState(*this);
//        std::swap(newState.field[emptyPos], newState.field[emptyPos - 1]);
//        newState.emptyPos--;
//        return newState;
//    }
//    
//    GameState MoveUp() const
//    {
//        assert(CanMoveUp());
//        
//        GameState newState(*this);
//        std::swap(newState.field[emptyPos], newState.field[emptyPos + LineSize]);
//        newState.emptyPos += LineSize;
//        return newState;
//    }
//    
//    GameState MoveDown() const
//    {
//        assert(CanMoveDown());
//        
//        GameState newState(*this);
//        std::swap(newState.field[emptyPos], newState.field[emptyPos - LineSize]);
//        newState.emptyPos -= LineSize;
//        return newState;
//    }
//    
//    bool operator==(const GameState &other) const
//    {
//        return field == other.field;
//    }
//    
//    int heuristic() const{
//        int h = 0;
//        for (int i = 0; i < field.size(); ++i) {
//            int row = i / LineSize;
//            int col = i % LineSize;
//            if (field[i] == 0) {
//                continue;
//            }
//            int goal_row = (field[i] - 1) / LineSize;
//            int goal_col = (field[i] - 1) % LineSize;
//            h += std::abs(row - goal_row) + std::abs(col - goal_col);
//        }
//        return h;
//    }
//    
//    bool operator<(const GameState &other) const {
//            return field < other.field;
//    }
//    
//private:
//    size_t getInvCount() const
//    {
//        size_t inv_count = 0;
//        for (int i = 0; i < FieldSize - 1; i++)
//        {
//            for (int j = i + 1; j < FieldSize; j++)
//            {
//                if (field[i] > field[j] && field[i] && field[j])
//                    inv_count++;
//            }
//        }
//        return inv_count;
//    }
//    
//    std::array<char, FieldSize> field;
//    char emptyPos;
//    
//    friend struct GameStateHasher;
//    friend std::ostream& operator<<(std::ostream &out, const GameState &state);
//};
//
//struct GameStateHasher
//{
//public:
//    size_t operator()(const GameState &state) const
//    {
//        size_t hash = 0;
//        std::memcpy(&hash, state.field.data(), sizeof(hash));
//        return hash;
//    }
//};
//
//std::ostream& operator<<(std::ostream &out, const GameState &state)
//{
//    for (int i = 0; i < 3; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            out << static_cast<int>(state.field[i * 3 + j]) << ' ';
//        }
//        out << std::endl;
//    }
//    return out;
//}
//
//std::string GetSolution(const std::array<char, FieldSize> &field)
//{
//    GameState startState(field);
//    
//    if (!startState.IsSolvable())
//        return "-1";
//    
//    std::unordered_map<GameState, char, GameStateHasher> visited;
//    visited[startState] = 'S';
//    
//    std::set<std::pair<int, GameState>> q;
//    q.insert({k * startState.heuristic(), startState});
//    
//    
//    while (true)
//    {
//        std::pair<int, GameState> edge = *(q.begin());
//        q.erase(q.begin());
//        GameState state = edge.second;
//        int state_len = edge.first;
//        
//        if (state.IsComplete())
//            break;
//        
//        if (state.CanMoveLeft())
//        {
//            GameState newState = state.MoveLeft();
//            if (visited.find(newState) == visited.end())
//            {
//                visited[newState] = 'L';
//                q.insert({state_len + k * newState.heuristic() + 1, newState});
//            }
//        }
//        if (state.CanMoveRight())
//        {
//            GameState newState = state.MoveRight();
//            if (visited.find(newState) == visited.end())
//            {
//                visited[newState] = 'R';
//                q.insert({state_len + k * newState.heuristic() + 1, newState});
//            }
//        }
//        if (state.CanMoveUp())
//        {
//            GameState newState = state.MoveUp();
//            if (visited.find(newState) == visited.end())
//            {
//                visited[newState] = 'U';
//                q.insert({state_len + k * newState.heuristic() + 1, newState});
//            }
//        }
//        if (state.CanMoveDown())
//        {
//            GameState newState = state.MoveDown();
//            if (visited.find(newState) == visited.end())
//            {
//                visited[newState] = 'D';
//                q.insert({state_len + k * newState.heuristic() + 1, newState});
//            }
//        }
//        
//        if (q.size() >= max_q) { //чистим очередь
//            auto it = q.begin();
//            std::advance(it, q.size() / 2);
//            q.erase(it, q.end());
//        }
//    }
//    
//    std::string path;
//    GameState state(finishField);
//    
//    while (visited[state] != 'S')
//    {
//        char move = visited[state];
//        switch (move)
//        {
//            case 'L':
//            {
//                state = state.MoveRight();
//                path += 'L';
//                break;
//            }
//            case 'R':
//            {
//                state = state.MoveLeft();
//                path += 'R';
//                break;
//            }
//            case 'D':
//            {
//                state = state.MoveUp();
//                path += 'D';
//                break;
//            }
//            case 'U':
//            {
//                state = state.MoveDown();
//                path += 'U';
//                break;
//            }
//        }
//        
//    }
//    
//    std::reverse(path.begin(), path.end());
//    return path;
//}
//
//int main(int argc, const char * argv[]) {
//    
//    std::array<char, FieldSize> field;
//    
//    for (size_t i = 0; i < FieldSize; ++i) {
//        int val;
//        std::cin >> val;
//        field[i] = static_cast<char>(val);
//    }
//    
//    std::string sol = GetSolution(field);
//    
//    std::cout << sol.size() << std::endl;
//    std::cout << sol << std::endl;
//    return 0;
//}


//рк

/*Проверить, является ли неориентированный граф деревом.*/

//#include <iostream>
//#include <vector>
//#include <cassert>
//#include <set>
//#include <stdio.h>
//#include <queue>
//
//#include <vector>
//
//struct IGraph {
//    virtual ~IGraph() {}
//        
//    virtual void AddEdge(int from, int to) = 0;
//
//    virtual int VerticesCount() const  = 0;
//
//    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
//    
//    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
//    
//    
//};
//
//class MatrixGraph : public IGraph {
//public:
//    explicit MatrixGraph(int size);
//    MatrixGraph(const IGraph& graph);
//    ~MatrixGraph() override = default;
//
//    void AddEdge(int from, int to) override;
//    int VerticesCount() const override;
//    std::vector<int> GetNextVertices(int vertex) const override;
//    std::vector<int> GetPrevVertices(int vertex) const override;
//
//private:
//    std::vector<std::vector<bool>> adjacencyMatrix;
//};
//
//MatrixGraph::MatrixGraph(int size)
//    : adjacencyMatrix(size, std::vector<bool>(size, false)) {}
//
//MatrixGraph::MatrixGraph(const IGraph &graph) :
//    adjacencyMatrix(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), false)) {
//    for (int from = 0; from < graph.VerticesCount(); ++from) {
//        for (int to: graph.GetNextVertices(from))
//        adjacencyMatrix[from][to] = true;
//    }
//}
//
//void MatrixGraph::AddEdge(int from, int to) {
//    assert(0 <= from && from < adjacencyMatrix.size());
//    assert(0 <= to && to < adjacencyMatrix.size());
//    adjacencyMatrix[from][to] = true;
//}
//
//int MatrixGraph::VerticesCount() const {
//    return (int)adjacencyMatrix.size();
//}
//
//std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
//    assert(0 <= vertex && vertex < adjacencyMatrix.size());
//    std::vector<int> nextVertices;
//    
//    for (int to = 0; to < adjacencyMatrix.size(); ++to) {
//        if (adjacencyMatrix[vertex][to]) nextVertices.push_back(to);
//    }
//    return nextVertices;
//}
//
//std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
//    assert(0 <= vertex && vertex < adjacencyMatrix.size());
//    std::vector<int> prevVertices;
//    
//    for (int from = 0; from < adjacencyMatrix.size(); ++from) {
//        if (adjacencyMatrix[from][vertex])
//            prevVertices.push_back(from);
//        }
//    return prevVertices;
//}
//
//void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
//{
//    std::queue<int> qu;
//    qu.push(vertex);
//    visited[vertex] = true;
//    
//    while (!qu.empty())
//    {
//        int currentVertex = qu.front();
//        qu.pop();
//        
//        func(currentVertex);
//        
//        for (int nextVertex: graph.GetNextVertices(currentVertex))
//        {
//            if (!visited[nextVertex])
//            {
//                visited[nextVertex] = true;
//                qu.push(nextVertex);
//            }
//        }
//    }
//}
//
//void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
//{
//    std::vector<bool> visited(graph.VerticesCount(), false);
//    
//    for (int i = 0; i < graph.VerticesCount(); ++i)
//    {
//        if (!visited[i])
//        {
//            BFS(graph, i, visited, func);
//        }
//    }
//}
//
//void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
//{
//    visited[vertex] = true;
//    func(vertex);
//    
//    for (int nextVertex: graph.GetNextVertices(vertex))
//    {
//        if (!visited[nextVertex])
//        {
//            DFS(graph, nextVertex, visited, func);
//        }
//    }
//}
//
//void mainDFS(const IGraph &graph, const std::function<void(int)> &func)
//{
//    std::vector<bool> visited(graph.VerticesCount(), false);
//    
//    for (int i = 0; i < graph.VerticesCount(); ++i)
//    {
//        if (!visited[i])
//        {
//            DFS(graph, i, visited, func);
//        }
//    }
//}
//
//bool DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, int parent)
//{
//    visited[vertex] = true;
//    
//    for (int nextVertex : graph.GetNextVertices(vertex)) {
//        if (!visited[nextVertex]) {
//            if (!DFS(graph, nextVertex, visited, vertex)) {
//                return false;
//            }
//        } 
//        else if (nextVertex != parent) {
//            return false;
//        }
//    }
//    return true;
//}
//
//int main() {
//    int n, m;
//    std::cin >> n >> m;
//    if (m != n - 1) {
//        std::cout << 0 << std::endl;
//        return 1;
//    }
//    
//    MatrixGraph graph(n);
//    
//    int from, to;
//    for (int i = 0; i < m; ++i) {
//        std::cin >> from >> to;
//        graph.AddEdge(from, to);
//        graph.AddEdge(to, from);
//    }
//    
//    std::vector<bool> visited(n, false);
//    
//    if (!DFS(graph, 0, visited, -1)) {
//        std::cout << 0 << std::endl;
//        return 1;
//    }
//    
//    for (auto i : visited) {
//        if (i == false) {
//            std::cout << 0 << std::endl;
//            return 1;
//        }
//    }
//    
//    std::cout << 1 << std::endl;
//    return 1;
//}


/* Нужно проверить, является ли неориентированный граф эйлеровым.*/


//#include <iostream>
//#include <vector>
//#include <cassert>
//#include <set>
//#include <stdio.h>
//#include <queue>
//
//#include <vector>
//
//struct IGraph {
//    virtual ~IGraph() {}
//        
//    virtual void AddEdge(int from, int to) = 0;
//
//    virtual int VerticesCount() const  = 0;
//
//    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
//    
//    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
//    
//    
//};
//
//class MatrixGraph : public IGraph {
//public:
//    explicit MatrixGraph(int size);
//    MatrixGraph(const IGraph& graph);
//    ~MatrixGraph() override = default;
//
//    void AddEdge(int from, int to) override;
//    int VerticesCount() const override;
//    std::vector<int> GetNextVertices(int vertex) const override;
//    std::vector<int> GetPrevVertices(int vertex) const override;
//
//private:
//    std::vector<std::vector<bool>> adjacencyMatrix;
//};
//
//MatrixGraph::MatrixGraph(int size)
//    : adjacencyMatrix(size, std::vector<bool>(size, false)) {}
//
//MatrixGraph::MatrixGraph(const IGraph &graph) :
//    adjacencyMatrix(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), false)) {
//    for (int from = 0; from < graph.VerticesCount(); ++from) {
//        for (int to: graph.GetNextVertices(from))
//        adjacencyMatrix[from][to] = true;
//    }
//}
//
//void MatrixGraph::AddEdge(int from, int to) {
//    assert(0 <= from && from < adjacencyMatrix.size());
//    assert(0 <= to && to < adjacencyMatrix.size());
//    adjacencyMatrix[from][to] = true;
//}
//
//int MatrixGraph::VerticesCount() const {
//    return (int)adjacencyMatrix.size();
//}
//
//std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
//    assert(0 <= vertex && vertex < adjacencyMatrix.size());
//    std::vector<int> nextVertices;
//    
//    for (int to = 0; to < adjacencyMatrix.size(); ++to) {
//        if (adjacencyMatrix[vertex][to]) nextVertices.push_back(to);
//    }
//    return nextVertices;
//}
//
//std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
//    assert(0 <= vertex && vertex < adjacencyMatrix.size());
//    std::vector<int> prevVertices;
//    
//    for (int from = 0; from < adjacencyMatrix.size(); ++from) {
//        if (adjacencyMatrix[from][vertex])
//            prevVertices.push_back(from);
//        }
//    return prevVertices;
//}
//
//
//
//void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited) {
//    std::queue<int> qu;
//    qu.push(vertex);
//    visited[vertex] = true;
//    
//    while (!qu.empty())
//    {
//        int currentVertex = qu.front();
//        qu.pop();
//        
//        for (int nextVertex: graph.GetNextVertices(currentVertex))
//        {
//            if (!visited[nextVertex])
//            {
//                visited[nextVertex] = true;
//                qu.push(nextVertex);
//            }
//        }
//    }
//}
//
//bool isConnect(const IGraph &graph) {
//    std::vector<bool> visited(graph.VerticesCount(), false);
//    int vertex = 0;
//    
//    for (int i = 0; i < graph.VerticesCount(); ++i) {
//        if (!graph.GetNextVertices(i).empty()) {
//            vertex = i;
//            break;
//        }
//    }
//    BFS(graph, vertex, visited);
//    
//    for (int i = 0; i < graph.VerticesCount(); ++i) {
//        if (!visited[i] and !graph.GetNextVertices(i).empty()) {
//            return false;
//        }
//    }
//    return true;
//}
//
//int main() {
//    int n, m;
//    std::cin >> n >> m;
//    
//    
//    MatrixGraph graph(n);
//    
//    int from, to;
//    for (int i = 0; i < m; ++i) {
//        std::cin >> from >> to;
//        graph.AddEdge(from, to);
//        graph.AddEdge(to, from);
//    }
//    
//    if (!isConnect(graph)) {
//        std::cout << 0 << std::endl;
//        return 0;
//    }
//    
//    int count = 0;
//    
//    for (int i = 0; i < graph.VerticesCount(); ++i) {
//        if (graph.GetNextVertices(i).size() % 2 != 0) {
//            count++;
//        }
//    }
//    
//    if (count == 0 or count == 2) {
//        std::cout << 1 << std::endl;
//        return 0;
//    }
//    
//    else {
//        std::cout << 0 << std::endl;
//        return 0;
//    }
//    
//    
//    return 0;
//}


/* Рику необходимо попасть на межвселенную конференцию. За каждую телепортацию он платит бутылками лимонада, поэтому хочет потратить их на дорогу как можно меньше (он же всё-таки на конференцию едет!). Однако после K перелетов подряд Рика начинает сильно тошнить, и он ложится спать на день. Ему известны все существующие телепортации. Теперь Рик хочет найти путь (наименьший по стоимости в бутылках лимонада), учитывая, что телепортация не занимает времени, а до конференции осталось 10 минут (то есть он может совершить не более K перелетов)!
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <limits>

using namespace std;

struct edge {
    int to, weight;
};

int main() {
    int n, m, k, s, f;
    cin >> n >> m >> k >> s >> f; //s-from, f-to

    s--;
    f--;

    vector<vector<edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, w;
        
        cin >> from >> to >> w;
        
        from--;
        to--;
        
        graph[from].push_back({to, w});
    }
    
    int intMax = 0x7FFFFFFF;
    vector<vector<int>> d(n, vector<int>(k + 1, intMax));
    d[s][0] = 0;

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;
    q.push({0, s, 0}); //weight, вершина, число телепорт

    while (!q.empty()) {
        auto [current_cost, u, t] = q.top();
        q.pop();

        if (current_cost > d[u][t]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to, w = edge.weight;

            if (t + 1 <= k and d[v][t + 1] > current_cost + w) {
                d[v][t + 1] = current_cost + w;
                q.push({d[v][t + 1], v, t + 1});
            }
        }
    }

    int minSum = intMax;
    for (int t = 0; t <= k; ++t) {
        minSum = min(minSum, d[f][t]);
    }
    

    if (minSum == intMax) {
        cout << -1 << endl;
    } else {
        cout << minSum << endl;
    }

    return 0;
}
