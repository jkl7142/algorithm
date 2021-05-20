/*
*       Exercise 22 : C++ 표준 라이브러리를 이용한 맵과 리듀스 구현
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

// 맵 연산 테스트 함수
void transform_test(std::vector<int> S) {
    std::vector<int> Tr;
    std::cout << "[맵 테스트]" << std::endl;
    std::cout << "입력 배열, S: ";
    for (auto i : S)
        std::cout << i << " ";
    std::cout << std::endl;

    // std::transform(), f(x) = x^2
    // 입력 벡터를 바꾸지 않고, 별도의 벡터를 만들어서 반환
    std::transform(S.begin(), S.end(), std::back_inserter(Tr),  // std::back_inserter(Tr) : Tr 벡터 맨 끝에 삽입
        [](int x) { return ceil(std::pow(x, 2.0)); });

    std::cout << "std::transform(), Tr: ";
    for (auto i : Tr)
        std::cout << i << " ";
    std::cout << std::endl;

    // std::for_each()
    // 입력 벡터 자체를 변경
    std::for_each(S.begin(), S.end(),
        [](int& x) { x = ceil(std::pow(x, 2.0)); });
    
    std::cout << "std::for_each(), S: ";
    for (auto i : S)
        std::cout << i << " ";
    std::cout << std::endl;
}

// 리듀스 연산 테스트 함수
void reduce_test(std::vector<int> S) {
    std::cout << std::endl << "[리듀스 테스트]" << std::endl;
    std::cout << "입력 배열, S: ";
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