/*
*       Activity 17 : 미로-순간이동 게임
*/

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <climits>
//#include <fstream>
#include <map>

using namespace std;

struct Edge {
    int src;
    int dst;
    int weight;
};

const int UNKNOWN = INT_MAX;

// 테스트 케이스 읽기 함수
bool ReadTestCase(vector<Edge> test, int& V, int& E, vector<Edge>& edges)
{

	for (int i = 0; i < E; i++)
	{
		int u = test[i].src;
        int v = test[i].dst;
        int w = test[i].weight;

		edges.push_back(Edge {u, v, w});
	}

	return true;
}

void FillStack(int node, vector<bool>& visited,
	vector<vector<int>>& adj, stack<int>& stack)
{
	visited[node] = true;

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			FillStack(next, visited, adj, stack);
		}
	}

	stack.push(node);
}

// 코사라주 전역 변수
vector<bool> isStuck;
vector<int> inComponent;
int componentIndex;

void CollectConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component)
{
	visited[node] = true;
	component.push_back(node);

	inComponent[node] = componentIndex;

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			CollectConnectedComponents(next, visited, adj, component);
		}
		else if (inComponent[node] != inComponent[next])
		{
			isStuck[inComponent[next]] = false;
		}
	}
}

vector<vector<int>> Transpose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transpose(V);

	for (int i = 0; i < V; i++)
	{
		for (auto next : adj[i])
		{
			transpose[next].push_back(i);
		}
	}

	return transpose;
}

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
    // 전역 변수 초기화
	isStuck.resize(V, true);
	inComponent.resize(V, UNKNOWN);
	componentIndex = 0;

	vector<bool> visited(V, false);
	stack<int> stack;

	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
	}

	vector<vector<int>> transpose = Transpose(V, adj);

	fill(visited.begin(), visited.end(), false);

	vector<vector<int>> connectedComponents;

	while (!stack.empty())
	{
		int node = stack.top();
		stack.pop();

		if (!visited[node])
		{
			vector<int> component;

			CollectConnectedComponents(node, visited, transpose, component);
			connectedComponents.push_back(component);
			componentIndex++;
		}
	}

	return connectedComponents;
}

bool HasNegativeCycle(const vector<Edge>& edges, vector<int> distance)
{
	for (auto& e : edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;

		if (distance[e.dst] > distance[e.src] + e.weight)
			return true;
	}

	return false;
}

int BellmanFord(vector<Edge> edges, int V, int start) {
    vector<int> distance(V, UNKNOWN);
    distance[start] = 0;

    // (V - 1)번 반복
    for (int i = 0; i < V - 1; i++) {
        // 전체 에지에 대해 반복
        for (auto& e : edges) {
            if (distance[e.src] == UNKNOWN)
                continue;

            if (distance[e.dst] > distance[e.src] + e.weight) {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }

    // 미로에 점수를 무한히 낮출 수 있는 경로가 있는지 판단
    // 음수 가중치 사이클이 있으면 UNKNOWN 반환
    if (HasNegativeCycle(edges, distance)) {
        return UNKNOWN;
    }

    int result = UNKNOWN;

    for (int i = 0; i < V; i++) {
        if (i == start) continue;

        result = min(result, distance[i]);
    }

    return result;
}

void print_test(vector<Edge> test, int V, int E, vector<Edge> edges) {

    ReadTestCase(test, V, E, edges);

    vector<vector<int>> adj(V + 1);

    for (auto& e : edges) {
        adj[e.src].push_back(e.dst);
    }

    vector<int> results;

    for (int i = 0; i < V; i++) {
        if (adj[i].empty()) {
            results.push_back(UNKNOWN);
            continue;
        }

        int shortest = BellmanFord(edges, V, i);

        if (shortest == UNKNOWN) {
            cout << "유효하지 않은 미로" << endl;
            exit(0);
        }

        results.push_back(shortest);
    }

    for (int i = 0; i < V; i++) {
        if (results[i] == UNKNOWN)
            cout << i << ": 고립된 방" << endl;
        else
            cout << i << ": " << results[i] << endl;
    }

    auto components = Kosaraju(V, adj);

    for (int i = 0; i < components.size(); i++) {
        if (isStuck[i]) {
            for (auto node : components[i]) {
                cout << node << " ";
            }

            cout << endl;
        }
    }
}

int main() {
    int V;
    vector<Edge> edges;

    // testcase 1 ~ 7
    map<int, vector<Edge>> test;

    test[0] = {{0, 1, 50}, {1, 0, -10},
                {1, 2, -10}, {2, 0, 0},
                {3, 0, 3}, {3, 4, 0},
                {4, 5, 1}, {5, 3, -2},
                {6, 0, -25}};
    test[1] = {{0, 3, 54}, {1, 0, -5},
                {1, 3, 6}, {2, 0, -44},
                {2, 3, -38}, {2, 1, -17},
                {3, 1, 96}, {4, 0, -44},
                {4, 3, 15}, {5, 2, 11},
                {5, 0, 44}, {5, 3, 91},
                {6, 1, 53}, {6, 2, 62},
                {6, 0, 77}, {7, 3, 68}};
    test[2] = {{0, 1, 90}, {1, 2, -16},
                {1, 0, 79}, {1, 3, 95},
                {2, 3, -89}, {3, 1, -23},
                {3, 0, -38}, {4, 1, -34},
                {5, 3, -38}, {6, 0, 59},
                {6, 2, 85}, {7, 4, 47},
                {7, 1, 85}, {7, 0, -44},
                {8, 0, -25}, {8, 2, 11},
                {9, 4, -95}};
    test[3] = {{0, 4, -40}, {1, 6, 92},
                {2, 3, 77}, {3, 1, 61},
                {3, 6, 7}, {3, 2, 81},
                {4, 2, 93}, {5, 2, 48},
                {6, 0, -27}, {6, 4, -77},
                {7, 5, -1}, {8, 3, -49},
                {8, 6, 52}, {8, 1, 70},
                {9, 6, 20}, {9, 0, 95},
                {9, 3, 1}, {10, 5, -17},
                {11, 1, 75}, {11, 0, -57},
                {12, 1, -62}, {12, 4, -5},
                {13, 3, -19}, {13, 6, 17},
                {13, 4, 94}, {14, 1, 63}};
    test[4] = {{0, 1, 5}, {0, 3, -3},
                {1, 2, 3}, {1, 4, 5},
                {2, 3, -7}, {2, 5, 8},
                {3, 7, 10}, {4, 2, -5},
                {5, 4, 12}, {5, 6, 13},
                {6, 2, -6}, {6, 7, 8},
                {7, 8, 5}, {8, 3, 4}};
    test[5] = {{0, 4, 1}, {1, 7, 1},
                {2, 0, 1}, {2, 4, 1},
                {2, 5, 1}, {3, 5, 1},
                {3, 8, 1}, {3, 13, 1},
                {3, 14, 1}, {3, 16, 1},
                {4, 2, 1}, {5, 4, 1},
                {5, 6, 1}, {6, 0, 1},
                {6, 4, 1}, {7, 1, 1},
                {8, 11, 1}, {9, 5, 1},
                {9, 6, 1}, {9, 15, 1},
                {10, 8, 1}, {10, 11, 1},
                {10, 12, 1}, {10, 17, 1},
                {11, 8, 1}, {11, 10, 1},
                {12, 8, 1}, {12, 11, 1},
                {13, 1, 1}, {13, 7, 1},
                {14, 3, 1}, {14, 6, 1},
                {14, 9, 1}, {14, 15, 1},
                {15, 13, 1}, {15, 17, 1},
                {17, 8, 1}, {17, 10, 1},
                {17, 11, 1}};
    test[6] = {{0, 2, 37}, {0, 5, -96},
                {0, 9, 72}, {1, 5, 33},
                {2, 9, -36}, {3, 2, 15},
                {3, 4, -11}, {4, 2, 46},
                {4, 7, -20}, {4, 10, 26},
                {5, 1, 14}, {6, 2, -1},
                {6, 3, 83}, {6, 10, -45},
                {7, 8, 70}, {7, 12, -47},
                {8, 7, 81}, {8, 11, -41},
                {9, 0, -1}, {10, 3, 23},
                {10, 6, 61}, {10, 7, 32},
                {12, 8, 40}, {12, 11, -64}};

    //ReadTestCase(test, V, edges);

    // print_test(test[0], 7, 9, edges);
    // print_test(test[1], 8, 16, edges);
    // print_test(test[2], 10, 17, edges);
    // print_test(test[3], 15, 26, edges);
    // print_test(test[4], 9, 14, edges);
    // sprint_test(test[5], 18, 39, edges);
    print_test(test[6], 13, 24, edges);

    return 0;
}