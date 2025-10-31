//
// Created by alice on 31.10.2025.
//
#include <algorithm>
#include <cassert>
#include <vector>
#include <numeric>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename Compare = std::less<>>
void order(std::vector<T> &vector, std::size_t left, std::size_t right, Compare comp = {}) {
    for (auto i = left + 1; i < right; ++i) {
        for (auto j = i; j > left; --j) {
            if (comp(vector[j], vector[j - 1])) {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename Compare = std::less<>>
std::size_t partition(std::vector<T> &vector, std::size_t left, std::size_t right, Compare comp = {}) {
    auto middle = left + (right - left) / 2;
    auto &a = vector[left];
    auto &b = vector[middle];
    auto &c = vector[right - 1];

    if (comp(b, a)) std::swap(a, b);
    if (comp(c, a)) std::swap(a, c);
    if (comp(c, b)) std::swap(b, c);

    auto pivot = vector[middle];

    auto i = left;
    auto j = right - 1;

    while (true) {
        while (comp(vector[++i], pivot)) {}
        while (comp(pivot, vector[--j])) {}

        if (i < j) {
            std::swap(vector[i], vector[j]);
        } else {
            break;
        }
    }

    return i;
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename Compare = std::less<>>
void quick_split(std::vector<T> &vector, std::size_t left, std::size_t right, Compare comp = {}) {
    if (right - left > 16) {
        auto pivot_index = partition(vector, left, right, comp);

        quick_split(vector, left, pivot_index, comp);
        quick_split(vector, pivot_index, right, comp);
    } else {
        order(vector, left, right, comp);
    }
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename Compare = std::less<>>
void sort(std::vector<T> &vector, Compare comp = {}) {
    if (vector.size() <= 1) return;

    quick_split(vector, 0, vector.size(), comp);
}

////////////////////////////////////////////////////////////////////////////////////

struct Person {
    std::string name;
    int age;

    bool operator<(const Person &other) const {
        return age < other.age;
    }

    bool operator==(const Person &other) const = default;
};

struct CompareByName {
    bool operator()(const Person &a, const Person &b) const {
        return a.name < b.name;
    }
};

////////////////////////////////////////////////////////////////////////////////////

int main() {

    auto size = 10000;
    std::vector<int> vector(size, 0);

    for (auto i = 0; i < size; ++i) {
        vector[i] = size - i;
    }

    sort(vector);
    assert(std::ranges::is_sorted(vector));
    std::vector<double> doubles = {3.14, 1.41, 2.71, 0.57};
    sort(doubles);
    assert(std::ranges::is_sorted(doubles));

    std::vector<std::string> strings = {"banana", "apple", "cherry"};
    sort(strings);
    assert(std::ranges::is_sorted(strings));

    std::vector<Person> people = {
            {"Alice",   25},
            {"Bob",     30},
            {"Charlie", 20}
    };
    sort(people);
    assert(std::ranges::is_sorted(people, {}, &Person::age));

    sort(people, CompareByName{});
    assert(std::ranges::is_sorted(people, CompareByName{}));

    std::vector<int> numbers = {1, 5, 3, 2, 4};
    sort(numbers, std::greater<>());
    assert(std::ranges::is_sorted(numbers, std::greater<>()));

    return 0;
}