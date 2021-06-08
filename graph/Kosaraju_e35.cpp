/*
*       Excercise 35 : 코사라주 알고리즘
*       강한 연결 요소 찾기 strongly connexted component
*/

#include <vector>
#include <stack>
#include <iostream>

using namespace std;

// DFS 함수 1
void FillStack(int node, vector<bool>& visited,
    vector<vector<int>>& adj, stack<int>& stack) {
    visited[node] = true;

    for (auto next : adj[node]) {
        if (!visited[next]) {
            FillStack(next, visited, adj, stack);
        }
    }

    stack.push(node);
}

// 전치 그래프 반환 함수
vector<vector<int>> Transpose(int V, vector<vector<int>> adj) {
    vector<vector<int>> transpose(V);

    for (int i = 0; i < V; i++) {
        for (auto next : adj[i]) {
            transpose[next].push_back(i);
        }
    }

    return transpose;
}

// DFS 함수 2
void CollectConnectedComponents(int node, vector<bool>& visited,
    vector<vector<int>>& adj, vector<int>& component) {
    visited[node] = true;
    component.push_back(node);

    for (auto next : adj[node]) {
        if (!visited[next]) {
            CollectConnectedComponents(next, visited, adj, component);
        }
    }
}

// 코사라주 알고리즘
vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj) {
    vector<bool> visited(V, false);
    stack<int> stack;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            FillStack(i, visited, adj, stack);
        }
    }

    vector<vector<int>> transpose = Transpose(V, adj);

    fill(visited.begin(), visited.end(), false);

    vector<vector<int>> connectedComponents;

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        if (!visited[node]) {
            vector<int> component;
            
            CollectConnectedComponents(node, visited, transpose, component);
            connectedComponents.push_back(component);
        }
    }

    return connectedComponents;
}

int main() {
    int V;
    vector<vector<int>> adj;

    // 테스트 인접 리스트 그래프
    V = 9;

    adj = {
        { 1, 3 },
        { 2, 4 },
        { 3, 5 },
        { 7 },
        { 2 },
        { 4, 6 },
        { 7, 2 },
        { 8 },
        { 3 }
    };

    vector<vector<int>> connectedComponents = Kosaraju(V, adj);

    cout << "강한 연결 요소 개수: " << connectedComponents.size() << endl;

    for (int i = 0; i < connectedComponents.size(); i++) {
        cout << "[" << i + 1 << "] ";

        for (auto node : connectedComponents[i])
            cout << node << " ";

        cout << endl;
    }

    return 0;
}