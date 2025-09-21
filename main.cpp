//
// Created by alice on 05.09.2025.
//
#include <iostream>
#include <cmath>

int main() {
    int n = 0;
    double m = 0;
    double sum = 0;
    double min = 10000000000;
    double max = -100000000000;
    double mean = 0;
    std::cin >> n;
    double array[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> m;
        array[i] = m;
        max = std::max(max, m);
        min = std::min(min, m);
        sum += m;
    }

    mean = sum / n;
    double a = 0;
    for (int i = 0; i < n; i++) {
        a += (array[i] - mean) * (array[i] - mean);
    }
    a /= n;
    double mean_square = std::sqrt(a);

    std::cout << "Min: " << min << std::endl;
    std::cout << "Max: " << max << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Mean Square:  " << mean_square << std::endl;
}