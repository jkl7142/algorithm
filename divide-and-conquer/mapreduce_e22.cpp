/*
*       Exercise 22 : C++ ǥ�� ���̺귯���� �̿��� �ʰ� ���ེ ����
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

// �� ���� �׽�Ʈ �Լ�
void transform_test(std::vector<int> S) {
    std::vector<int> Tr;
    std::cout << "[�� �׽�Ʈ]" << std::endl;
    std::cout << "�Է� �迭, S: ";
    for (auto i : S)
        std::cout << i << " ";
    std::cout << std::endl;

    // std::transform(), f(x) = x^2
    // �Է� ���͸� �ٲ��� �ʰ�, ������ ���͸� ���� ��ȯ
    std::transform(S.begin(), S.end(), std::back_inserter(Tr),  // std::back_inserter(Tr) : Tr ���� �� ���� ����
        [](int x) { return ceil(std::pow(x, 2.0)); });

    std::cout << "std::transform(), Tr: ";
    for (auto i : Tr)
        std::cout << i << " ";
    std::cout << std::endl;

    // std::for_each()
    // �Է� ���� ��ü�� ����
    std::for_each(S.begin(), S.end(),
        [](int& x) { x = ceil(std::pow(x, 2.0)); });
    
    std::cout << "std::for_each(), S: ";
    for (auto i : S)
        std::cout << i << " ";
    std::cout << std::endl;
}

// ���ེ ���� �׽�Ʈ �Լ�
void reduce_test(std::vector<int> S) {
    std::cout << std::endl << "[���ེ �׽�Ʈ]" << std::endl;
    std::cout << "�Է� �迭, S: ";
    for (auto i : S)
        std::cout << i << " ";
    std::cout << std::endl;

    // std::accumulate()
    auto ans = std::accumulate(S.begin(), S.end(), 0, 
        [](int acc, int x) { return acc + x; });
    std::cout << "std::accumulate(), ans: " << ans << std::endl;
}

int main() {
    std::vector<int> S {1, 10, 4, 7, 3, 5, 6, 9, 8, 2};

    transform_test(S);
    reduce_test(S);

    return 0;
}