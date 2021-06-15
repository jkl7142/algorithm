/*
*       Activity 18 : 여행 경로
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;

LL TravelItinerary(int n, vector<int> distance) {
    reverse(distance.begin(), distance.end());

    vector<LL> DP(n + 1, 0);

    DP[0] = 1;

    for (int i = 1; i <= n; i++) {
        int dist = distance[i - 1];
        for (int j = 1; j <= dist; j++) {
            DP[i] = (DP[i] + DP[i - j]) % MOD;
        }
    }

    return DP[n];
}

int main() {

    int n;
    cin >> n;

    vector<int> distance(n);

    for (int i = 0; i < n; i++) {
        cin >> distance[i];
    }
    
    LL result = TravelItinerary(n, distance);
    cout << result << endl;

    return 0;
}