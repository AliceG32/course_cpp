#include <algorithm>
#include <cassert>
#include <vector>
#include <numeric>

////////////////////////////////////////////////////////////////////////////////////

void order(std::vector<int> &vector, std::size_t left, std::size_t right) {
    for (auto i = left + 1; i < right; ++i) {
        for (auto j = i; j > left; --j) {
            if (vector[j - 1] > vector[j]) {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////

std::size_t partition(std::vector<int> &vector, std::size_t left, std::size_t right) {
    auto middle = std::midpoint(left, right);
    auto &a = vector[left];
    auto &b = vector[middle];
    auto &c = vector[right - 1];

    if (a > b) std::swap(a, b);
    if (a > c) std::swap(a, c);
    if (b > c) std::swap(b, c);

    auto pivot = vector[middle];

    auto i = left;
    auto j = right - 1;

    while (true) {
        while (vector[++i] < pivot) {}

        while (vector[--j] > pivot) {}

        if (i < j) {
            std::swap(vector[i], vector[j]);
        } else {
            break;
        }
    }

    return i;
}

////////////////////////////////////////////////////////////////////////////////////

void quick_split(std::vector<int> &vector, std::size_t left, std::size_t right) {
    if (right - left > 16) {
        auto pivot_index = partition(vector, left, right);

        quick_split(vector, left, pivot_index);
        quick_split(vector, pivot_index + 1, right);
    } else {
        order(vector, left, right);
    }
}

////////////////////////////////////////////////////////////////////////////////////

void sort(std::vector<int> &vector) {
    if (vector.size() <= 1) return;

    quick_split(vector, 0, std::size(vector));
}

////////////////////////////////////////////////////////////////////////////////////

int main() {
    auto size = 10000;
    std::vector<int> vector(size, 0);

    for (auto i = 0; i < size; ++i) {
        vector[i] = size - i;
    }

    sort(vector);

    assert(std::ranges::is_sorted(vector));

    return 0;
}