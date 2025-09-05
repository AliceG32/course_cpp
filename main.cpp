//
// Created by alice on 05.09.2025.
//
#include <iostream>

int main() {
    double epsilon;

    std::cin >> epsilon;

    double e = 1.0;
    double term = 1.0;
    int n = 1;

    while (term >= epsilon) {
        term /= n;
        e += term;
        n++;
    }

    std::cout << e << std::endl;

    return 0;
}