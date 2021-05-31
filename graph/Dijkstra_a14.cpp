/*
*       Activity 14 : 뉴욕에서 최단 경로 찾기 (다익스트라)
*/

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <limits>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
struct Edge {
    unsigned src;
    unsigned dst;
    T weight;
};

template <typename T>
class Graph {
public:
    Graph(unsigned N) : V(N) {}

    auto vertices() const { return V; }

    auto& edges() const { return edge_list; }

    auto edges(unsigned v) const {
        vector<Edge<T>> edges_from_v;
        for (auto& e : edge_list) {
            if (e.src == v)
                edges_from_v.emplace_back(e);
        }

        return edges_from_v;
    }

    void add_edge(Edge<T>&& e) {
        if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
            edge_list.emplace_back(e);
        else
            cerr << "에러: 유효 범위를 벗어난 정점!" << endl;
    }

private:
    unsigned V;
    vector<Edge<T>> edge_list;
};

template <typename U>
ostream& operator<< (ostream& os, const Graph<U>& G) {
    for (unsigned i = 1; i < G.vertices(); i++) {
        os << i << ":\t";
        auto edges = G.edges(i);
        for (auto& e : edges)
            os << "{" << e.dst << ": " << e.weight << "}, ";

        os << endl;
    }

    return os;
}

// 파일을 읽어 그래프 객체를 생성하는 함수
template <typename T>
auto read_graph_from_file() {
    ifstream infile("USA-road-d.NY.gr");
    
    if (infile.fail()) {
        cerr << "파일을 찾을 수 없음" << endl;
        exit(100);
    }

    unsigned num_vertices, num_edges;

    string line;

    // 'p'로 시작하는 문제 설명 행 읽기
    // p <num_vertices> <num_edges>
    while (getline(infile, line)) {
        if (line[0] == 'p') {
            istringstream iss(line);
            char p;
            string sp;
            iss >> p >> sp >> num_vertices >> num_edges;
            cout << "정점 개수: " << num_vertices << endl;
            cout << "에지 개수: " << num_edges << endl;
            break;
        }
    }

    Graph<T> G(num_vertices + 1);

    // 'a'로 시작하는 에지 표현 행 읽기
    // a <source_vertex> <destination_vertex> <weight>
    while (getline(infile, line)) {
        if (line[0] == 'a') {
            istringstream iss(line);

            char p;
            unsigned source_vertex, dest_vertex;
            T weight;
            iss >> p >> source_vertex >> dest_vertex >> weight;

            G.add_edge(Edge<T>{source_vertex, dest_vertex, weight});
        }
    }

    infile.close();
    return G;
}

template <typename T>
struct Label {
    unsigned ID;
    T distance;

    inline bool operator> (const Label<T>& l) const {
        return this->distance > l.distance;
    }
};

template <typename T>
auto dijkstra_shortest_path(const Graph<T>& G, unsigned src, unsigned dst) {
    priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;

    vector<T> distance(G.vertices(), numeric_limits<T>::max());

    set<unsigned> visited;
    vector<unsigned> parent(G.vertices());

    heap.emplace(Label<T>{src, 0});
    parent[src] = src;

    while (!heap.empty()) {
        auto current_vertex = heap.top();
        heap.pop();

        if (current_vertex.ID == dst) {
            break;
        }

        if (visited.find(current_vertex.ID) == visited.end()) {
            for (auto& e : G.edges(current_vertex.ID)) {
                auto neighbor = e.dst;
                auto new_distance = current_vertex.distance + e.weight;

                if (new_distance < distance[neighbor]) {
                    heap.emplace(Label<T>{neighbor, new_distance});

                    parent[neighbor] = current_vertex.ID;
                    distance[neighbor] = new_distance;
                }
            }

            visited.insert(current_vertex.ID);
        }
    }

    vector<unsigned> shortest_path;
    auto current_vertex = dst;

    while (current_vertex != src) {
        shortest_path.push_back(current_vertex);
        current_vertex = parent[current_vertex];
    }

    shortest_path.push_back(src);
    reverse(shortest_path.begin(), shortest_path.end());

    return shortest_path;
}

int main() {

    using T = unsigned;

    auto G = read_graph_from_file<T>();

    unsigned src_id = 913;
    unsigned dst_id = 542;

    auto shortest_path = dijkstra_shortest_path<T>(G, src_id, dst_id);

    cout << endl << "[" << src_id << " 정점에서 " << dst_id << " 정점까지의 최단 경로]" << endl;
    for (auto v : shortest_path)
        cout << v << " ";
    cout << endl;

    return 0;
}