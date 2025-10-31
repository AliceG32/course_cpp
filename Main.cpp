//
// Created by alice on 31.10.2025.
//
#include <cassert>
#include <limits>
#include <cmath>
#include <type_traits>

void process_max(double &result, double arg) {
    result = std::fmax(result, arg);
}

void process_min(double &result, double arg) {
    result = std::fmin(result, arg);
}

void process_sum(double &result, double arg) {
    result += arg;
}

void process_average(double &sum, int &count, double arg) {
    sum += arg;
    ++count;
}

template<typename... Args>
double max_double(Args... args) {
    double result = std::numeric_limits<double>::lowest();

    ((std::is_same_v<Args, double> ? process_max(result, args) : void()), ...);

    return result;
}

template<typename... Args>
double min_double(Args... args) {
    double result = std::numeric_limits<double>::max();

    ((std::is_same_v<Args, double> ? process_min(result, args) : void()), ...);

    return result;
}

template<typename... Args>
double sum_double(Args... args) {
    double result = 0.0;

    ((std::is_same_v<Args, double> ? process_sum(result, args) : void()), ...);

    return result;
}

template<typename... Args>
double average_double(Args... args) {
    double sum = 0.0;
    int count = 0;

    ((std::is_same_v<Args, double> ? process_average(sum, count, args) : void()), ...);

    return count > 0 ? sum / count : 0.0;
}

int main() {
    assert(max_double(1.1, 2.2, 3.3) == 3.3);
    assert(min_double(1.1, 2.2, 3.3) == 1.1);
    assert(sum_double(1.0, 2.0, 3.0) == 6.0);
    assert(average_double(1.0, 2.0, 3.0) == 2.0);

    assert(max_double(1.5, 2, 4.1) == 4.1);
    assert(min_double(1.5, 0.7, 4) == 0.7);
    assert(sum_double(1, 3.5, 4.5) == 8.0);

    return 0;
}