//
// Created by alice on 02.11.2025.
//
#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template<typename... Ts>
class Tuple {
public:

    static constexpr std::size_t size() noexcept {
        return sizeof...(Ts);
    }
};

//////////////////////////////////////////////////////////////////

template<typename T, typename... Ts>
class Tuple<T, Ts...> {
public:
    explicit constexpr Tuple(T &&x, Ts &&... ys)
            : m_head(std::forward<T>(x)),
              m_tail(std::forward<Ts>(ys)...) {}

    static constexpr std::size_t size() noexcept {
        return sizeof...(Ts) + 1;
    }

    template<std::size_t I>
    [[nodiscard]] constexpr auto get() const {
        if constexpr (I > 0) {
            return m_tail.template get<I - 1>();
        } else {
            return m_head;
        }
    }

private:
    T m_head;
    Tuple<Ts...> m_tail;
};

//////////////////////////////////////////////////////////////////

int main() {
    Tuple<int, double, std::string> tuple(1, 2.0, "a");

    assert(tuple.size() == 3);
    assert(tuple.get<0>() == 1);
    assert(tuple.get<1>() == 2.0);
    assert(tuple.get<2>() == "a");

    Tuple<int> single_tuple(42);
    static_assert(Tuple<int>::size() == 1);
    assert(single_tuple.size() == 1);
    assert(single_tuple.get<0>() == 42);

    Tuple<> empty_tuple;
    static_assert(Tuple<>::size() == 0);
    assert(empty_tuple.size() == 0);

    constexpr Tuple<int, double> tuple4(10, 3.14);
    static_assert(tuple4.get<0>() == 10);
    static_assert(tuple4.get<1>() == 3.14);

    constexpr Tuple<int, Tuple<double, char>> tuple5(5, Tuple<double, char>(2.5, 'x'));
    static_assert(tuple5.size() == 2);
    static_assert(tuple5.get<0>() == 5);
    static_assert(tuple5.get<1>().size() == 2);

    return 0;
}