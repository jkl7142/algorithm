/*
*       Activity 15 : 욕심쟁이 로봇
*/

#include <vector>
#include <iostream>
#include <climits>
#include <fstream>
#include <map>

using namespace std;

struct Edge {
    int src;
    int dst;
    int weight;
};

const int UNKNOWN = INT_MAX;    // 무한대 표현

// 텍스트 파일을 불러와 그래프의 에지 리스트를 만드는 함수
bool ReadTestCase(vector<pair<string, int>> test, int& N, vector<Edge>& edges) {

    for (int i = 0; i < N * N - 1; i++) {
        string directions;
        int power;

        directions = test[i].first;
        power = test[i].second;

        int next = i;
        for (auto d : directions) {
            switch (d) {
            case 'N' : next = i - N; break;
            case 'E' : next = i + 1; break;
            case 'S' : next = i + N; break;
            case 'W' : next = i - 1; break;
            }

            // power 값의 부호를 바꿔서 에지 가중치로 사용
            edges.push_back(Edge {i, next, -power});
        }
    }

    return true;
}

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

    // 음수 가중치 사이클이 있는지 검사
    for (auto& e : edges) {
        if (distance[e.src] == UNKNOWN)
            continue;

        if (distance[e.dst] > distance[e.src] + e.weight) {
            cout << "음수 가중치 사이클 발견!" << endl;
            return {};
        }
    }

    return distance;
}

// 테스트 결과 출력 함수
void print_test(vector<pair<string, int>> test, int& tN, int N, vector<Edge> edges) {
    if (ReadTestCase(test, N, edges)) {
        vector<int> distance = BellmanFord(edges, N * N, 0);
        if (distance.empty() || distance[N * N - 1] == UNKNOWN)
            cout << "testcase " << tN << " : "<< "탐색 중단" << endl;
        else
            cout << "testcase " << tN << " : " << -1 * distance[N * N - 1] << endl;
    }
    tN++;
}

int main() {

    int N;
    vector<Edge> edges;
    
    // testcase 1 ~ 5
    map<int, vector<pair<string, int>>> test;
    test[0] = {{"SE", -10}, {"SE", -8}, {"S", -6}, {"S", 7},
                {"E", -10}, {"S", 20}, {"E", -1}, {"NE", 5}};
    test[1] = {{"S", -83}, {"E", -77}, {"SE", -93}, {"S", 86},
                {"SE", -49}, {"N", -62}, {"SE", -90}, {"S", -63},
                {"S", 40}, {"NW", -72}, {"SW", -11}, {"W", 67},
                {"E", -82}, {"N", -62}, {"E", -67}};
    test[2] = {{"E", -1}, {"E", -5}, {"S", 6}, {"S", -2},
                {"W", 15}, {"W", -10}, {"E", -5}, {"NE", 5}};
    test[3] = {{"SE", -83}, {"SE", -77}, {"E", -93}, {"S", 86},
                {"W", -49}, {"E", -62}, {"SE", -90}, {"N", -63},
                {"SEW", 40}, {"NS", -72}, {"S", -11}, {"W", 67},
                {"NW", -82}, {"W", -62}, {"SW", -67}, {"S", 29},
                {"W", 22}, {"SW", 69}, {"W", -93}, {"SW", -11},
                {"E", 29}, {"E", -21}, {"E", -84}, {"E", -98}};
    test[4] = {{"S", 8}, {"E", -2}, {"SEW", -15}, {"SE", 4},
                {"S", 25}, {"S", -26}, {"NEW", 19}, {"NS", 7},
                {"SEW", -56}, {"S", 11}, {"E", 25}, {"N", -86},
                {"SEW", 11}, {"NE", 26}, {"S", -78}, {"NS", -11},
                {"NSW", -76}, {"SW", 33}, {"NSW", 4}, {"SW", -40},
                {"E", 8}, {"E", 11}, {"E", 36}, {"E", -2}};

    int tN = 0;

    // testcase1~5 입력을 받아 결과 확인
    print_test(test[tN], tN, 3, edges);
    print_test(test[tN], tN, 4, edges);
    print_test(test[tN], tN, 3, edges);
    print_test(test[tN], tN, 5, edges);
    print_test(test[tN], tN, 5, edges);

    return 0;
}