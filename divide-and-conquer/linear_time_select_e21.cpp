/*
*       Exercise 21 : 선형 시간 선택
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
auto find_median(typename std::vector<T>::iterator begin,
                 typename std::vector<T>::iterator last) {
    // 정렬
    quick_sort<T>(begin, last);

    // 가운데(median) 원소 반복자를 반환
    return begin + (std::distance(begin, last) / 2);
}

// 피벗 위치 반복자를 인자로 받는 분할 함수
template <typename T>
auto partition_using_given_pivot(typename std::vector<T>::iterator begin,
                                typename std::vector<T>::iterator end,
                                typename std::vector<T>::iterator pivot) {
    auto left_iter = begin;
    auto right_iter = end;

    while (true) {
        while (*left_iter < *pivot && left_iter != right_iter) {
            left_iter++;
        }

        while (*right_iter >= *pivot && left_iter != right_iter) {
            right_iter--;
        }

        if (left_iter == right_iter)
            break;
        else
            std::iter_swap(left_iter, right_iter);
    }

    if (*pivot > *right_iter)
        std::iter_swap(pivot, right_iter);

    return right_iter;
}

// 선형 시간 검색 알고리즘
template <typename T>
typename std::vector<T>::iterator linear_time_select(typename std::vector<T>::iterator begin,
                                                     typename std::vector<T>::iterator last,
                                                     size_t i) {
    auto size = std::distance(begin, last);

    if (size > 0 && i < size) {
        // 다섯 개 원소로 구분하여 만들 부분 벡터 Vi의 개수 계산
        auto num_Vi = (size + 4) / 5;
        size_t j = 0;

        // 각각의 Vi에서 중앙값을 찾아 벡터 M에 저장
        std::vector<T> M;
        for (; j < size / 5; j++) {
            auto b = begin + (j * 5);
            auto l = begin + (j * 5) + 5;

            M.push_back(*find_median<T>(b, l));
        }

        // 마지막 벡터
        if (j * 5 < size) {
            auto b = begin + (j * 5);
            auto l = begin + (j * 5) + (size % 5);

            M.push_back(*find_median<T>(b, l));
        }

        // Vi의 중앙값으로 구성된 벡터 M에서 다시 중앙값 q를 찾음
        auto median_of_medians = (M.size() == 1) ? M.begin() :
            linear_time_select<T>(M.begin(), M.end() - 1, M.size() / 2);

        // 분할 연산을 적용하고 피벗 q의 위치 k를 찾음
        auto partition_iter = partition_using_given_pivot<T>(begin, last, median_of_medians);
        auto k = std::distance(begin, partition_iter) + 1;

        if (i == k)
            return partition_iter;
        else if (i < k)
            return linear_time_select<T>(begin, partition_iter - 1, i);
        else
            return linear_time_select<T>(partition_iter + 1, last, i - k);
    }
    else {
        return begin;
    }
}

// i번째 원소가 정확한지 확인하기 위한 병합 정렬 함수
template <typename T>
std::vector<T> merge(std::vector<T>& arr1, std::vector<T>& arr2) {
    std::vector<T> merged;

    auto iter1 = arr1.begin();
    auto iter2 = arr2.begin();

    while (iter1 != arr1.end() && iter2 != arr2.end()) {
        if (*iter1 < *iter2) {
            merged.emplace_back(*iter1);
            iter1++;
        }
        else {
            merged.emplace_back(*iter2);
            iter2++;
        }
    }

    if (iter1 != arr1.end()) {
        for (; iter1 != arr1.end(); iter1++) {
            merged.emplace_back(*iter1);
        }
    }
    else {
        for (; iter2 != arr2.end(); iter2++) {
            merged.emplace_back(*iter2);
        }
    }

    return merged;
}

template <typename T>
std::vector<T> merge_sort(std::vector<T> arr) {
    if (arr.size() > 1) {
        auto mid = size_t(arr.size() / 2);
        auto left_half = merge_sort(std::vector<T>(arr.begin(), arr.begin() + mid));
        auto right_half = merge_sort(std::vector<T>(arr.begin() + mid, arr.end()));

        return merge<T>(left_half, right_half);
    }

    return arr;
}

template <typename T>
void print_vector(std::vector<T> arr) {
    for (auto i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}

void run_linear_select_test() {
    std::vector<int> S1 {45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7};
    std::cout << "입력 벡터:" << std::endl;
    print_vector<int>(S1);

    std::cout << "정렬된 벡터:" << std::endl;
    print_vector<int>(merge_sort<int>(S1));

    std::cout << "3번째 원소: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 3) << std::endl;
    std::cout << "5번째 원소: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 5) << std::endl;
    std::cout << "11번째 원소: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 11) << std::endl;
}

int main() {
    run_linear_select_test();
    return 0;
}