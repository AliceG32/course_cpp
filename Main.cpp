//
// Created by alice on 24.09.2025.
//
#include <iostream>
#include <cmath>
#include <numeric>
#include <cassert>

int gcd(int a, int b){
    if (b == a){
        return a;
    }
    return gcd(b, a % b);
}
int lcm(int a, int b){
    return a /gcd(a, b) * b; // меньше шансов на переполнение
}
int main(){
    assert(gcd(15, 25 == std::gcd(15, 25)));
}