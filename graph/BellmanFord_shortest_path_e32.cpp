/*
*       Exercise 32 : 벨만-포드 알고리즘 구현
*/

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct Edge {
    int src;
    int dst;
    int weight;
};

const int UNKNOWN = INT_MAX;    // 무한대 표현

vector<int> BellmanFord(vector<Edge> edges, int V, int start) {
    vector<int> distance(V, UNKNOWN);
    distance[start] = 0;

    // (V - 1)번 반복
    for (int i = 0; i < V - 1; i++) {
        // 전체 에지에 대해 반복
        for (auto& e : edges) {
            // 에지의 시작 정점의 거리 값이 UNKNOWN이면 스킵
            if (distance[e.src] == UNKNOWN)
                continue;

            // 새로운 경로에 의한 거리값이 인접한 정점의 거리 값보다 작으면
            // 거리 값을 업데이트함
            if (distance[e.dst] > distance[e.src] + e.weight) {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }

    return distance;
}

int main() {
    int V = 5;          // 정점 개수
    vector<Edge> edges; // 에지 포인터의 벡터

    vector<vector<int>> edge_map {  // {시작 정점, 목표 정점, 가중치}
        {0, 1, 3},
        {1, 2, 5},
        {1, 3, 10},
        {3, 2, -7},
        {2, 4, 2}
    };

    for (auto& e : edge_map) {
        edges.emplace_back(Edge {e[0], e[1], e[2]});
    }

    int start = 0;
    vector<int> distance = BellmanFord(edges, V, start);

    cout << "[" << start << "번 정점으로부터 최소 거리]" << endl;

    for (int i = 0; i < distance.size(); i++) {
        if (distance[i] == UNKNOWN)
            cout << i << "번 정점: 방문하지 않음!" << endl;
        else
            cout << i << "번 정점: " << distance[i] << endl;
    }

    return 0;
}