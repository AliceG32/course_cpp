//
// Created by alice on 13.12.2025.
//
import rational;

#include <cassert>
#include <vector>
#include <sstream>
#include <memory>
#include <variant>
#include <optional>
#include <stdexcept>
#include <iostream>

int main() {
    try {
        using namespace math;

        Rational x = 1, y(2, 1);
        assert(equal(static_cast<double>(x), 1));

        try {
            Rational zero_denom(1, 0);
            assert(false && "Should have thrown Exception");
        }
        catch (const Exception &e) {
            std::cerr << "Caught custom exception: " << e.what() << "\n";
        }

        try {
            std::size_t huge_size = static_cast<std::size_t>(1) << 62;
            auto ptr = new char[huge_size];
            delete[] ptr;
        }
        catch (const std::bad_alloc &e) {
            std::cerr << "Caught std::bad_alloc: " << e.what() << "\n";
        }

        try {
            std::variant<int, std::string> v = 42;
            std::string s = std::get<std::string>(v);
        }
        catch (const std::bad_variant_access &e) {
            std::cerr << "Caught std::bad_variant_access: " << e.what() << "\n";
        }

        try {
            std::optional<int> opt;
            int value = opt.value();
        }
        catch (const std::bad_optional_access &e) {
            std::cerr << "Caught std::bad_optional_access: " << e.what() << "\n";
        }

        try {
            std::vector<int> vec;
            vec.reserve(vec.max_size() + 1);
        }
        catch (const std::length_error &e) {
            std::cerr << "Caught std::length_error: " << e.what() << "\n";
        }

        try {
            std::vector<int> vec = {1, 2, 3};
            int value = vec.at(10);
        }
        catch (const std::out_of_range &e) {
            std::cerr << "Caught std::out_of_range: " << e.what() << "\n";
        }

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

        assert(stream_2.str() == "1/2");

        std::stringstream bad_stream("1/0");
        try {
            bad_stream >> x;
            assert(false && "Should throw Exception");
        }
        catch (const Exception &e) {
            std::cerr << "Caught custom exception in stream input: " << e.what() << "\n";
        }

    }
    catch (const std::exception &e) {
        std::cerr << "Caught std::exception: " << e.what() << "\n";
        return 1;
    }
    catch (...) {
        std::cerr << "Caught unknown exception\n";
        return 1;
    }

    return 0;
}