//
// Created by alice on 13.12.2025.
//
module;

#include <iostream>
#include <numeric>

module rational;

namespace math {

    void Rational::reduce() {
        if (m_den < 0) {
            m_num = -m_num;
            m_den = -m_den;
        }

        auto gcd = std::gcd(m_num, m_den);
        m_num /= gcd;
        m_den /= gcd;
    }

    Rational::Rational(int num, int den) : m_num(num), m_den(den) {
        if (m_den == 0) {
            throw Exception("Denominator can't be zero");
        }
        reduce();
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
        if (other.m_num == 0) {
            throw Exception("Division by zero in Rational::operator/=");
        }
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

        return lhs_num <=> rhs_num;
    }

    bool operator==(const Rational &lhs, const Rational &rhs) {
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }

    std::istream &operator>>(std::istream &stream, Rational &rational) {
        char slash;
        int num, den;

        if (!(stream >> num)) {
            throw std::runtime_error("Failed to read numerator");
        }

        if (!(stream >> slash) || slash != '/') {
            throw std::runtime_error("Invalid format: expected '/'");
        }

        if (!(stream >> den)) {
            throw std::runtime_error("Failed to read denominator");
        }

        if (den == 0) {
            throw Exception("Denominator cannot be zero in input stream");
        }

        rational = Rational(num, den);
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const Rational &rational) {
        return stream << rational.m_num << '/' << rational.m_den;
    }
}