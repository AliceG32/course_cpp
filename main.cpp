//
// Created by alice on 05.09.2025.
//
#include <iostream>
#include <cmath>

int main() {
    const double epsilon = 1e-6;
    double a;
    double b;
    double c;
    double discriminant;
    double x1;
    double x2;

    std::cin >> a;
    std::cin >> b;
    std::cin >> c;


    discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        std::cout << "нет решений";
    } else {
        if (discriminant < epsilon) {
            x1 = b * (-1) - sqrt(discriminant);
            std::cout << x1;
        } else {
            x1 = (b * (-1) - sqrt(discriminant))/(2*a);
            x2 = (b * (-1) + sqrt(discriminant))/(2*a);
            std::cout << x1 << std::endl;
            std::cout << x2;
        }
    }
    return 0;
}