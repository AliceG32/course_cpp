//
// Created by alice on 24.11.2025.
//
#include <cassert>
#include <cmath>
#include <compare>
#include <iostream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class addable {
    friend T operator+(T lhs, T const &rhs) { return lhs += rhs; }

    friend T operator+(T const &lhs, int rhs) { return lhs + T(rhs); }

    friend T operator+(int lhs, T const &rhs) { return T(lhs) + rhs; }
};

template<typename T>
class subtractable {
    friend T operator-(T lhs, T const &rhs) { return lhs -= rhs; }

    friend T operator-(T const &lhs, int rhs) { return lhs - T(rhs); }

    friend T operator-(int lhs, T const &rhs) { return T(lhs) - rhs; }
};

template<typename T>
class multipliable {
    friend T operator*(T lhs, T const &rhs) { return lhs *= rhs; }

    friend T operator*(T const &lhs, int rhs) { return lhs * T(rhs); }

    friend T operator*(int lhs, T const &rhs) { return T(lhs) * rhs; }
};

template<typename T>
class dividable {
    friend T operator/(T lhs, T const &rhs) { return lhs /= rhs; }

    friend T operator/(T const &lhs, int rhs) { return lhs / T(rhs); }

    friend T operator/(int lhs, T const &rhs) { return T(lhs) / rhs; }
};


template<typename T>
class incrementable {

    friend T operator++(T &obj, int) {
        T x = obj;
        ++obj;
        return x;
    }
};

template<typename T>
class decrementable {

    friend T operator--(T &obj, int) {
        T x = obj;
        --obj;
        return x;
    }
};

//  -------------------------------------------------------------------------------------------

class Rational : public addable<Rational>,
                 public subtractable<Rational>,
                 public multipliable<Rational>,
                 public dividable<Rational>,
                 public incrementable<Rational>,
                 public decrementable<Rational> {
private:
    int m_num = 0, m_den = 1;

    void reduce() {
        if (m_den < 0) {
            m_num = -m_num;
            m_den = -m_den;
        }

        auto common_divisor = std::gcd(m_num, m_den);

        m_num /= common_divisor;
        m_den /= common_divisor;
    }

public:
    Rational(int num = 0, int den = 1) : m_num(num), m_den(den) {
        assert(den != 0 && "Denominator must not be zero");
        reduce();
    }

    explicit operator double() const {
        return 1.0 * m_num / m_den;
    }

    auto &operator+=(Rational const &other) {
        auto least_common_multiple = std::lcm(m_den, other.m_den);

        m_num = m_num * (least_common_multiple / m_den) + other.m_num * (least_common_multiple / other.m_den);

        m_den = least_common_multiple;

        reduce();

        return *this;
    }

    auto &operator-=(Rational const &other) {
        return *this += Rational(other.m_num * -1, other.m_den);
    }

    auto &operator*=(Rational const &other) {
        m_num *= other.m_num;

        m_den *= other.m_den;

        reduce();

        return *this;
    }

    auto &operator/=(Rational const &other) {
        assert(other.m_num != 0 && "Division by zero rational");
        return *this *= Rational(other.m_den, other.m_num);
    }

    auto &operator++() {
        *this += 1;
        return *this;
    }

    auto &operator--() {
        *this -= 1;
        return *this;
    }

    friend std::strong_ordering operator<=>(Rational const &lhs, Rational const &rhs) {
        long long lhs_num = static_cast<long long>(lhs.m_num) * rhs.m_den;
        long long rhs_num = static_cast<long long>(rhs.m_num) * lhs.m_den;
        return lhs_num <=> rhs_num;
    }

// -------------------------------------------------------------------------------------------

    friend bool operator==(Rational const &lhs, Rational const &rhs) {
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }


//  -------------------------------------------------------------------------------------------

    friend auto &operator>>(std::istream &stream, Rational &rational) {
        return (stream >> rational.m_num).ignore() >> rational.m_den;
    }

//  -------------------------------------------------------------------------------------------

    friend auto &operator<<(std::ostream &stream, Rational const &rational) {
        return stream << rational.m_num << '/' << rational.m_den;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6) {
    return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    Rational x = 1, y(2, 1);

// -----------------------------------------------------------------------

    std::vector<int> vector_2(5);
    std::vector<int> vector_3 = {1, 2, 3, 4, 5};

// -----------------------------------------------------------------------

    assert(equal(static_cast < double > (x), 1));

// -----------------------------------------------------------------------

    assert((x += y) == Rational(+3, 1));
    assert((x -= y) == Rational(+1, 1));
    assert((x *= y) == Rational(+2, 1));
    assert((x /= y) == Rational(+1, 1));

// -----------------------------------------------------------------------

    assert((x++) == Rational(+1, 1));
    assert((x--) == Rational(+2, 1));
    assert((++y) == Rational(+3, 1));
    assert((--y) == Rational(+2, 1));

// -----------------------------------------------------------------------

    assert((x + y) == Rational(+3, 1));
    assert((x - y) == Rational(-1, 1));
    assert((x * y) == Rational(+2, 1));
    assert((x / y) == Rational(+1, 2));

// -----------------------------------------------------------------------

    assert((x += 1) == Rational(+2, 1));
    assert((x + 1) == Rational(+3, 1));
    assert((1 + y) == Rational(+3, 1));
    assert((1 + 1) == Rational(+2, 1));

// -----------------------------------------------------------------------


    // x = 2/1, y = 2/1
    assert((x <=> y) == std::strong_ordering::equal);
    assert((x == y) == true);
    assert((x != y) == false);
    assert((x < y) == false);
    assert((x > y) == false);
    assert((x <= y) == true);
    assert((x >= y) == true);

    Rational a(1, 2), b(3, 4);
    assert((a <=> b) == std::strong_ordering::less);
    assert((a == b) == false);
    assert((a != b) == true);
    assert((a < b) == true);
    assert((a > b) == false);
    assert((a <= b) == true);
    assert((a >= b) == false);

    Rational c(3, 4), d(1, 2);
    assert((c <=> d) == std::strong_ordering::greater);
    assert((c == d) == false);
    assert((c != d) == true);
    assert((c < d) == false);
    assert((c > d) == true);
    assert((c <= d) == false);
    assert((c >= d) == true);

// -----------------------------------------------------------------------

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;

// -----------------------------------------------------------------------

    stream_1 >> x;
    stream_2 << x;

// -----------------------------------------------------------------------

    assert(stream_2.str() == stream_1.str());

}