#include <iostream>
#include <cmath>

int main(){
    int n;
    double result;

    std::cin >> n;
    result = (pow((1 + sqrt(5)) / 2, n) - pow((1 - sqrt(5)) / 2, n)) / sqrt(5);
    std::cout << result;

    return 0;
}