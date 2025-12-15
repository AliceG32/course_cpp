//
// Created by alice on 15.12.2025.
//
#include <algorithm>
#include <cassert>
#include <vector>
#include <numeric>
#include <iterator>
#include <string>
#include <random>
#include <gtest/gtest.h>

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


class HybridSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::random_device rd;
        gen = std::mt19937(rd());
    }

    std::mt19937 gen;
};

TEST_F(HybridSortTest, EmptyVector) {
std::vector<int> vec;
sort(vec);
EXPECT_TRUE(vec.empty());
}

TEST_F(HybridSortTest, SingleElement) {
std::vector<int> vec = {42};
sort(vec);
ASSERT_EQ(vec.size(), 1);
EXPECT_EQ(vec[0], 42);
}

TEST_F(HybridSortTest, AlreadySorted) {
std::vector<int> vec = {1, 2, 3, 4, 5};
sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, ReverseSorted) {
std::vector<int> vec = {5, 4, 3, 2, 1};
sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, RandomNumbers) {
std::vector<int> vec(1000);
std::iota(vec.begin(), vec.end(), 1);
std::shuffle(vec.begin(), vec.end(), gen);

sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, LargeRandomArray) {
std::vector<int> vec(10000);
std::iota(vec.begin(), vec.end(), 1);
std::shuffle(vec.begin(), vec.end(), gen);

sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, Duplicates) {
std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, AllSameElements) {
std::vector<int> vec(100, 7);
sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, DescendingOrder) {
std::vector<int> vec = {9, 8, 7, 6, 5, 4, 3, 2, 1};
sort(vec, std::greater<>());
EXPECT_TRUE(std::ranges::is_sorted(vec, std::greater<>()));
}

TEST_F(HybridSortTest, DoublePrecision) {
std::vector<double> vec = {3.14, 1.41, 2.71, 0.57, 1.73, 2.23};
sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, Strings) {
std::vector<std::string> vec = {"banana", "apple", "cherry", "date", "elderberry"};
sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, CustomStructByAge) {
std::vector<Person> vec = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20},
        {"David", 35},
        {"Eve", 22}
};

sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec, {}, &Person::age));
}

TEST_F(HybridSortTest, CustomStructByName) {
std::vector<Person> vec = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20},
        {"David", 35},
        {"Eve", 22}
};

sort(vec, CompareByName{});
EXPECT_TRUE(std::ranges::is_sorted(vec, CompareByName{}));
}

TEST_F(HybridSortTest, EdgeCaseSize16) {
std::vector<int> vec(16);
std::iota(vec.rbegin(), vec.rend(), 1);

sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, EdgeCaseSize17) {
std::vector<int> vec(17);
std::iota(vec.rbegin(), vec.rend(), 1);

sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, StabilityCheckForInsertionSortPart) {
std::vector<std::pair<int, int>> vec = {
        {1, 1}, {2, 1}, {1, 2}, {3, 1}, {2, 2}
};

sort(vec, [](const auto& a, const auto& b) {
return a.first < b.first;
});

EXPECT_TRUE(std::ranges::is_sorted(vec, {}, &std::pair<int, int>::first));
}

TEST_F(HybridSortTest, VerySmallArrays) {
for (int size = 1; size <= 5; ++size) {
std::vector<int> vec(size);
std::iota(vec.rbegin(), vec.rend(), 1);

sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec)) << "Failed for size " << size;
}
}

TEST_F(HybridSortTest, NegativeNumbers) {
std::vector<int> vec = {-5, -1, -3, 0, 2, -4, 1};
sort(vec);
EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST_F(HybridSortTest, MixedTypesWithCustomComparator) {
std::vector<int> vec = {1, 5, 3, 2, 4};
sort(vec, std::greater<>());
EXPECT_TRUE(std::ranges::is_sorted(vec, std::greater<>()));
}

int main(int argc, char **argv) {
    {
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
                {"Alice", 25},
                {"Bob", 30},
                {"Charlie", 20}
        };
        sort(people);
        assert(std::ranges::is_sorted(people, {}, &Person::age));

        sort(people, CompareByName{});
        assert(std::ranges::is_sorted(people, CompareByName{}));

        std::vector<int> numbers = {1, 5, 3, 2, 4};
        sort(numbers, std::greater<>());
        assert(std::ranges::is_sorted(numbers, std::greater<>()));
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
