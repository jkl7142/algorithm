/*
*       Exercise 38 : �޸������̼��� �̿��Ͽ� �κ������� �� ���ϱ�
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include <climits>

using namespace std;

#define DEBUG 0
#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

vector<string> types = {
    "BRUTE FORCE",
    "BACKTRACKING",
    "MEMOIZATION",
    "TABULATION"
};

const int UNKNOWN = INT_MAX;

void GetAllSubsets(vector<int> set, vector<int> subset, int index,
                    vector<vector<vector<int>>>& allSubsets) {
    // ���� set�� ���� �ٴٸ� ���
    if (index == set.size()) {
        // �κ����� ũ�⸦ �ε����� ����Ͽ� �κ������� allSubsets�� �߰�
        allSubsets[subset.size()].push_back(subset);
        return;
    }

    // ���Ҹ� �߰����� �ʰ� ��� ȣ��
    GetAllSubsets(set, subset, index + 1, allSubsets);

    // ���Ҹ� �κ����տ� �߰��� �� ��� ȣ��
    subset.push_back(set[index]);
    GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target) {
    vector<vector<vector<int>>> allSubsets(set.size() + 1);

    GetAllSubsets(set, {}, 0, allSubsets);

    for (int size = 0; size <= set.size(); size++) {
        PRINT("�κ������� ���� ����: " << size << endl);

        for (auto subset : allSubsets[size]) {
            PRINT("\t{ ");

            int sum = 0;
            for (auto number : subset) {
                sum += number;
                PRINT(number << " ");
            }

            PRINT("} = " << sum << endl);

            if (sum == target)
                return true;
        }
    }

    return false;
}

bool SubsetSum_Backtracking(vector<int> &set, int sum, int i) {
    // ���� ���� �κ������� ���� target�� ���ٸ�
    if (sum == 0) {
        return true;
    }

    // ���� ���� �κ������� ���� target���� ũ�ų�, ������ ���� �����ߴٸ�
    if (set[i] > sum || i == set.size()) {
        return false;
    }

    // Case 1: sum���� set[i]�� ���� ��� ȣ��(i��° ���Ҹ� �κ����տ� �߰�)
    // Case 2: sum�� �״�� �����Ͽ� ��� ȣ��(i��° ���Ҹ� �κ����տ� �߰����� ����)
    return SubsetSum_Backtracking(set, sum - set[i], i + 1)
        || SubsetSum_Backtracking(set, sum, i + 1);
}

bool SubsetSum_Memoization(vector<int>& set, int sum, int i,
    vector<vector<int>> &memo) {
    // ���� ���� �κ������� ���� target�� ���ٸ�
    if (sum == 0) {
        return true;
    }

    // ���� ���� �κ������� ���� target���� ũ�ų�, ������ ���� �����ߴٸ�
    if (set[i] > sum || i == set.size()) {
        return false;
    }

    // ���� ���°� ĳ�ÿ� �ִ��� Ȯ��
    // ĳ�ÿ� �ִٸ� ���ȣ���� ���ϹǷ� ȿ���� ����
    if (memo[i][sum] == UNKNOWN) {
        // ���� ���¿� ���� �ַ���� ���Ͽ� ĳ�ÿ� ����
        bool append = SubsetSum_Memoization(set, sum - set[i], i + 1, memo);
        bool ignore = SubsetSum_Memoization(set, sum, i + 1, memo);

        memo[i][sum] = append || ignore;
    }

    // ĳ�ÿ� ����� ���� ��ȯ
    // i : Ű, sum : �����, memo[i][sum] : ��Ī��
    return memo[i][sum];
}

void GetTime(clock_t& timer, string type) {
    // ���� �ð����� timer�� ���� ��� �ð��� ���
    timer = clock() - timer;

    // ȭ�鿡 ��� �ð� ���
    cout << type << " ��� ��� �ð�: ";
    cout << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();    // timer�� ���� �ð����� �ʱ�ȭ
}

int main() {

    vector<int> set = {16, 1058, 22, 13, 46, 55, 3, 92, 47, 7,
                       98, 367, 807, 106, 333, 85, 577, 9, 3059};
    
    int target = 6799;
    int tests = 3;

    sort(set.begin(), set.end());

    for (int i = 0; i < tests; i++) {
        bool found;

        clock_t timer = clock();

        switch(i) {
        case 0:
            found = SubsetSum_BruteForce(set, target);
            break;
        case 1:
            found = SubsetSum_Backtracking(set, target, 0);
            break;
        case 2:
            // �޸������̼� ���̺� �ʱ�ȭ
            vector<vector<int>> memo(set.size(), vector<int>(7000, UNKNOWN));

            found = SubsetSum_Memoization(set, target, 0, memo);
            break;
        }

        if (found)
            cout << "���� ���� " << target << "�� �κ������� �ֽ��ϴ�." << endl;
        else
            cout << "���� ���� " << target << "�� �κ������� �����ϴ�." << endl;

        GetTime(timer, types[i]);
        cout << endl;
    }

    return 0;
}