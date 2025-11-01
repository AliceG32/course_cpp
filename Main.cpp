//
// Created by alice on 01.11.2025.
//
#include <array>
#include <iostream>

consteval double compute_e(double epsilon) {
    double e = 1.0;
    double term = 1.0;
    int n = 1;

    while (term >= epsilon) {
        term /= n;
        e += term;
        n++;
    }

    return e;
}

constexpr std::array<double, 5> epsilons = {1e-1, 1e-2, 1e-3, 1e-6};

int main() {

    static_assert(compute_e(epsilons[0]) > 2.5 && compute_e(epsilons[0]) < 2.8);
    static_assert(compute_e(epsilons[1]) > 2.70 && compute_e(epsilons[1]) < 2.73);
    static_assert(compute_e(epsilons[2]) > 2.718 && compute_e(epsilons[2]) < 2.719);
    static_assert(compute_e(epsilons[3]) > 2.718280 && compute_e(epsilons[3]) < 2.718282);

    return 0;
}