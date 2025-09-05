#include <iostream>

//
// Created by alice on 05.09.2025.
//

int main() {

    for (int i = 1; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {

                int number = i * 100 + j * 10 + k;

                int sum_of_cubes = i * i * i + j * j * j + k * k * k;

                if (number == sum_of_cubes) {
                    std::cout << number << std::endl;
                }
            }
        }
    }

    return 0;
}
