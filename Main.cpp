//
// Created by alice on 01.11.2025.
//

template<int N>
struct Fibonacci {

    static_assert(N >= 0, "N не должно быть отрицательным");
    static_assert(N < 47, "N должно быть меньше 47, чтобы int не переполнился");

    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

template<int N>
constexpr int fibonacci_v = Fibonacci<N>::value;

int main() {
    static_assert(fibonacci_v<0> == 0);
    static_assert(fibonacci_v<1> == 1);

    static_assert(fibonacci_v<2> == 1);
    static_assert(fibonacci_v<3> == 2);
    static_assert(fibonacci_v<4> == 3);
    static_assert(fibonacci_v<5> == 5);
    static_assert(fibonacci_v<6> == 8);
    static_assert(fibonacci_v<7> == 13);
    static_assert(fibonacci_v<8> == 21);
    static_assert(fibonacci_v<9> == 34);
    static_assert(fibonacci_v<10> == 55);
    static_assert(fibonacci_v<46> == 1836311903);

    constexpr int fib_10 = fibonacci_v<10>;
    static_assert(fib_10 == 55);

    return 0;
}