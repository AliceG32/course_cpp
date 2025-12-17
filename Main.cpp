//
// Created by alice on 31.10.2025.
//
#include <vector>
#include <cassert>
#include <type_traits>

template<typename Container, typename T>
void check(Container &container, T &&arg) {
    if constexpr (std::is_same_v<std::decay_t<T>, int>) {
        container.push_back(std::forward<T>(arg));
    }
}

template<typename Container, typename... Args>
void push_back_ints(Container &container, Args &&... args) {
    ((check(container, std::forward<Args>(args))), ...);
}

int main() {
    std::vector<int> vec;

    push_back_ints(vec, 1, 2, 3, 4, 5);
    assert(vec.size() == 5);
    assert(vec[0] == 1 && vec[1] == 2 && vec[2] == 3 && vec[3] == 4 && vec[4] == 5);
    assert(vec.back() == 5);

    std::vector<int> vec2;
    push_back_ints(vec2, 42);
    assert(vec2.size() == 1);
    assert(vec2[0] == 42);

    std::vector<int> vec3;
    push_back_ints(vec3);
    assert(vec3.empty());

    std::vector<int> vec4;
    push_back_ints(vec4, 10, 3.14, "hello", 20, 'a', 30);
    assert(vec4.size() == 3);
    assert(vec4[0] == 10 && vec4[1] == 20 && vec4[2] == 30);

    std::vector<int> vec5;
    push_back_ints(vec5, 3.14, "test", 'c');
    assert(vec5.empty());

    return 0;
}