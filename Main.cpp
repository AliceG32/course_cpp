//
// Created by alice on 30.11.2025.
//
#include "rational.h"
#include <cassert>
#include <sstream>
#include <vector>

int main() {
    Rational x = 1, y(2, 1);

    assert(equal(static_cast<double>(x), 1.0));

    assert((x += y) == Rational(3, 1));
    assert((x -= y) == Rational(1, 1));
    assert((x *= y) == Rational(2, 1));
    assert((x /= y) == Rational(1, 1));

    assert((x++) == Rational(1, 1));
    assert((x--) == Rational(2, 1));
    assert((++y) == Rational(3, 1));
    assert((--y) == Rational(2, 1));

    assert((x + y) == Rational(3, 1));
    assert((x - y) == Rational(-1, 1));
    assert((x * y) == Rational(2, 1));
    assert((x / y) == Rational(1, 2));

    assert((x <=> y) == std::strong_ordering::equal);
    assert((x == y) == true);

    Rational a(1, 2), b(3, 4);
    assert((a <=> b) == std::strong_ordering::less);
    assert((a == b) == false);

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;
    stream_1 >> x;
    stream_2 << x;
    assert(stream_2.str() == "1/2");

    return 0;
}