//
// Created by alice on 13.12.2025.
//
module;

#include <compare>
#include <iostream>
#include <cmath>
#include <stdexcept>

export module rational;

export namespace math {

    class Exception : public std::exception {
    public:
        explicit Exception(const char *message) : msg_(message) {}

        const char *what() const noexcept override {
            return msg_;
        }

    private:
        const char *msg_;
    };

    class Rational {
    public:
        Rational(int num = 0, int den = 1);

        explicit operator double() const {
            return 1.0 * m_num / m_den;
        }

        auto operator++(int) {
            auto x = *this;
            *this += 1;
            return x;
        }

        auto operator--(int) {
            auto x = *this;
            *this -= 1;
            return x;
        }

        auto &operator++() {
            *this += 1;
            return *this;
        }

        auto &operator--() {
            *this -= 1;
            return *this;
        }

        Rational &operator+=(const Rational &other);

        Rational &operator-=(const Rational &other);

        Rational &operator*=(const Rational &other);

        Rational &operator/=(const Rational &other);

        friend Rational operator+(Rational lhs, const Rational &rhs);

        friend Rational operator-(Rational lhs, const Rational &rhs);

        friend Rational operator*(Rational lhs, const Rational &rhs);

        friend Rational operator/(Rational lhs, const Rational &rhs);

        friend std::strong_ordering operator<=>(const Rational &lhs, const Rational &rhs);

        friend bool operator==(const Rational &lhs, const Rational &rhs);

        friend std::istream &operator>>(std::istream &stream, Rational &rational);

        friend std::ostream &operator<<(std::ostream &stream, const Rational &rational);

    private:
        void reduce();

        int m_num = 0, m_den = 1;
    };

    inline bool equal(double x, double y, double epsilon = 1e-6) {
        return std::abs(x - y) < epsilon;
    }
}