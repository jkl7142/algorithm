/*
*       Exercise 20 : 퀵 정렬 Quick Sort
*/

#include <iostream>
#include <vector>

// 피벗을 기준으로 분할
template <typename T>
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
    // 3개의 반복자 생성
    // 피벗, 벡터의 시작, 벡터의 마지막
    auto pivot_val = *begin;
    auto left_iter = begin + 1;
    auto right_iter = end;

    while (true) {
        // 벡터의 첫 번째 원소부터 시작하여 피벗보다 큰 원소를 찾습니다.
        while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
            left_iter++;

        // 벡터의 마지막 원소부터 시작하여 피벗보다 작은 원소를 찾습니다.
        while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
            right_iter--;

        // 만약 left_iter와 right_iter가 같다면 교환할 원소가 없음을 의미
        // 그렇지 않으면 *left_iter와 *right_iter를 서로 교환
        if (left_iter == right_iter)
            break;
        else
            // iter_swap(a, b) : a와 b가 가리키고 있는 원소의 값을 교환
            std::iter_swap(left_iter, right_iter);
    }

    // 오른쪽 배열의 시작 원소보다 피벗(벡터의 첫 번째 원소)이 크다면 서로 교환
    // 피벗보다 큰 원소는 오른쪽 부분, 피벗보다 작거나 같은 원소는 왼쪽 부분
    if (pivot_val > *right_iter)
        std::iter_swap(begin, right_iter);

    return right_iter;
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last) {
    // 만약 벡터에 하나 이상의 원소가 있다면
    if (std::distance(begin, last) >= 1) {
        // 분할 수행
        auto partition_iter = partition<T>(begin, last);
        // 분할 작업에 의해 생성된 벡터를 재귀적으로 정렬
        quick_sort<T>(begin, partition_iter - 1);
        quick_sort<T>(partition_iter, last);
    }
}

template <typename T>
void print_vector(std::vector<T> arr) {
    for (auto i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}

void run_quick_sort_test() {
    std::vector<int>    S1 {45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};
    std::vector<float>  S2 {45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f};
    std::vector<double> S3 {45.6, 1.0, 3.8, 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0};
    std::vector<char>    C {'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y'};

    std::cout << "정렬되지 않은 입력 벡터:" << std::endl;
    print_vector<int>(S1);
    print_vector<float>(S2);
    print_vector<double>(S3);
    print_vector<char>(C);
    std::cout << std::endl;

    quick_sort<int>(S1.begin(), S1.end() - 1);
    quick_sort<float>(S2.begin(), S2.end() - 1);
    quick_sort<double>(S3.begin(), S3.end() - 1);
    quick_sort<char>(C.begin(), C.end() - 1);


    std::cout << "퀵 정렬에 의해 정렬된 벡터:" << std::endl;
    print_vector<int>(S1);
    print_vector<float>(S2);
    print_vector<double>(S3);
    print_vector<char>(C);
    std::cout << std::endl;
}

int main() {

    run_quick_sort_test();

    return 0;
}