//
// Created by alice on 01.11.2025.
//
#include <cassert>
#include <numeric>

//////////////////////////////////////////////////////////////////////////////////////////

template<int N = 0, int D = 1>
struct Ratio {
    static_assert(D != 0, "Denominator cannot be zero");

    constexpr static auto num = N;
    constexpr static auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename R>
struct Reduce {
private:
    constexpr static auto gcd = std::gcd(R::num, R::den);

public:
    constexpr static auto num = R::num / gcd;
    constexpr static auto den = R::den / gcd;

    using type = Ratio<num, den>;
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename R1, typename R2>
struct Sum {
private:
    constexpr static auto num = R1::num * R2::den + R2::num * R1::den;
    constexpr static auto den = R1::den * R2::den;

public:
    using type = typename Reduce<Ratio<num, den>>::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename R1, typename R2>
struct Sub {
private:
    using NegativeR2 = Ratio<-R2::num, R2::den>;

public:
    using type = typename Sum<R1, NegativeR2>::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename R1, typename R2>
struct Mul {
private:
    constexpr static auto num = R1::num * R2::num;
    constexpr static auto den = R1::den * R2::den;

public:
    using type = typename Reduce<Ratio<num, den>>::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename R1, typename R2>
struct Div {
    static_assert(R2::num != 0, "Division by zero");

private:
    using ReciprocalR2 = Ratio<R2::den, R2::num>;

public:
    using type = typename Mul<R1, ReciprocalR2>::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename R1, typename R2> using sum = typename Sum<R1, R2>::type;
template<typename R1, typename R2> using sub = typename Sub<R1, R2>::type;
template<typename R1, typename R2> using mul = typename Mul<R1, R2>::type;
template<typename R1, typename R2> using div = typename Div<R1, R2>::type;

//////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename R = Ratio<1>>
struct Duration {
    T x = T();

    constexpr explicit Duration(T value = T()) : x(value) {}
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(Duration<T1, R1> const &lhs, Duration<T2, R2> const &rhs) {
    using ratio_t = Ratio<1, sum<R1, R2>::den>;

    auto x =
            (
                    lhs.x * ratio_t::den / R1::den * R1::num +
                    rhs.x * ratio_t::den / R2::den * R2::num
            );

    return Duration<decltype(x), ratio_t>(x);
}

//////////////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename R1, typename T2, typename R2>
constexpr auto operator-(Duration<T1, R1> const &lhs, Duration<T2, R2> const &rhs) {
    auto negative_rhs = Duration<T2, R2>(-rhs.x);
    return lhs + negative_rhs;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main() {
    static_assert(std::is_same_v<sum<Ratio<1, 2>, Ratio<1, 3>>, Ratio<5, 6>>);
    static_assert(std::is_same_v<sub<Ratio<1, 2>, Ratio<1, 3>>, Ratio<1, 6>>);
    static_assert(std::is_same_v<mul<Ratio<1, 2>, Ratio<2, 3>>, Ratio<1, 3>>);
    static_assert(std::is_same_v<div<Ratio<1, 2>, Ratio<2, 3>>, Ratio<3, 4>>);

    static_assert(std::is_same_v<sum<Ratio<2, 4>, Ratio<0, 1>>, Ratio<1, 2>>);
    static_assert(std::is_same_v<mul<Ratio<2, 3>, Ratio<3, 4>>, Ratio<1, 2>>);

    static_assert(std::is_same_v<sum<Ratio<2>, Ratio<3>>, Ratio<5>>);
    static_assert(std::is_same_v<sub<Ratio<5>, Ratio<3>>, Ratio<2>>);

    Duration<int, Ratio<1, 2>> duration_1(1);
    Duration<int, Ratio<1, 3>> duration_2(2);
    auto duration_3 = duration_1 + duration_2;
    assert(duration_3.x == 7);

    Duration<int, Ratio<1, 2>> duration_4(5);
    Duration<int, Ratio<1, 3>> duration_5(2);
    auto duration_6 = duration_4 - duration_5;
    assert(duration_6.x == 11);

    return 0;
}