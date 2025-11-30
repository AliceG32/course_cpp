//
// Created by alice on 30.11.2025.
//
#include "rational.h"
#include <numeric>
#include <cmath>

Rational::Rational(int num, int den) : m_num(num), m_den(den) {
    reduce();
}

void Rational::reduce() {
    if (m_den < 0) {
        m_num = -m_num;
        m_den = -m_den;
    }

    auto gcd = std::gcd(m_num, m_den);
    m_num /= gcd;
    m_den /= gcd;
}

Rational &Rational::operator+=(const Rational &other) {
    auto lcm = std::lcm(m_den, other.m_den);
    m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
    m_den = lcm;
    reduce();
    return *this;
}

Rational &Rational::operator-=(const Rational &other) {
    return *this += Rational(-other.m_num, other.m_den);
}

Rational &Rational::operator*=(const Rational &other) {
    m_num *= other.m_num;
    m_den *= other.m_den;
    reduce();
    return *this;
}

Rational &Rational::operator/=(const Rational &other) {
    return *this *= Rational(other.m_den, other.m_num);
}

Rational operator+(Rational lhs, const Rational &rhs) {
    return lhs += rhs;
}

Rational operator-(Rational lhs, const Rational &rhs) {
    return lhs -= rhs;
}

Rational operator*(Rational lhs, const Rational &rhs) {
    return lhs *= rhs;
}

Rational operator/(Rational lhs, const Rational &rhs) {
    return lhs /= rhs;
}

std::strong_ordering operator<=>(const Rational &lhs, const Rational &rhs) {
    long long lhs_num = static_cast<long long>(lhs.m_num) * rhs.m_den;
    long long rhs_num = static_cast<long long>(rhs.m_num) * lhs.m_den;

    if (lhs_num < rhs_num) {
        return std::strong_ordering::less;
    } else if (lhs_num > rhs_num) {
        return std::strong_ordering::greater;
    } else {
        return std::strong_ordering::equal;
    }
}

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
}

std::istream &operator>>(std::istream &stream, Rational &rational) {
    return (stream >> rational.m_num).ignore() >> rational.m_den;
}

std::ostream &operator<<(std::ostream &stream, const Rational &rational) {
    return stream << rational.m_num << '/' << rational.m_den;
}

