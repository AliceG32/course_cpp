//
// Created by alice on 30.11.2025.
//
import rational;
#include <cassert>
#include <vector>
#include <sstream>

int main() {
    using namespace math;
    Rational x = 1, y(2, 1);

    assert(equal(static_cast < double > (x), 1));


    assert((x += y) == Rational(+3, 1));
    assert((x -= y) == Rational(+1, 1));
    assert((x *= y) == Rational(+2, 1));
    assert((x /= y) == Rational(+1, 1));

    assert((x++) == Rational(+1, 1));
    assert((x--) == Rational(+2, 1));
    assert((++y) == Rational(+3, 1));
    assert((--y) == Rational(+2, 1));

    assert((x + y) == Rational(+3, 1));
    assert((x - y) == Rational(-1, 1));
    assert((x * y) == Rational(+2, 1));
    assert((x / y) == Rational(+1, 2));

    assert((x += 1) == Rational(+2, 1));
    assert((x + 1) == Rational(+3, 1));
    assert((1 + y) == Rational(+3, 1));
    assert((1 + 1) == Rational(+2, 1));


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

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;

    stream_1 >> x;
    stream_2 << x;

    assert(stream_2.str() == stream_1.str());

}