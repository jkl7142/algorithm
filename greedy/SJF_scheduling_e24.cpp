/*
*       Exercise 24 : 최단 작업 우선 스케줄링 Shortest-Job-First
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T>
auto compute_waiting_times(std::vector<T>& service_times) {
    std::vector<T> W(service_times.size());
    W[0] = 0;

    // i번째 대기시간 = i - 1번째 대기시간 + i - 1번째 작업시간
    for (auto i = 1; i < service_times.size(); i++)
        W[i] = W[i - 1] + service_times[i - 1];

    return W;
}

template <typename T>
void print_vector(std::vector<T>& V) {
    for (auto& i : V) {
        // 출력 칸을 2칸으로 설정
        std::cout.width(2);
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void compute_and_print_waiting_times(std::vector<T>& service_times) {
    auto waiting_times = compute_waiting_times<int>(service_times);

    std::cout << "- 처리 시간: ";
    print_vector<T>(service_times);

    std::cout << "- 대기 시간: ";
    print_vector<T>(waiting_times);

    auto ave_waiting_times = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();
    std::cout << "- 평균 대기 시간: " << ave_waiting_times;

    std::cout << std::endl;
}

int main() {

    std::vector<int> service_times {8, 1, 2, 4, 9, 2, 3, 5};

    std::cout << "[처음 일 처리 시간 & 대기 시간]" << std::endl;
    compute_and_print_waiting_times<int>(service_times);

    // 일 처리 시간을 오름차순으로 정렬
    std::sort(service_times.begin(), service_times.end());

    std::cout << std::endl;
    std::cout << "[정렬 후 일 처리 시간 & 대기 시간]" << std::endl;
    compute_and_print_waiting_times<int>(service_times);

    return 0;
}