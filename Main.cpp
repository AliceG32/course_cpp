//
// Created by alice on 21.09.2025.
//
#include <iostream>
#include <vector>

size_t collatz_length(unsigned long long int n, std::vector<size_t> &cache) {
    if (n == 1) return 1;

    if (n < cache.size() && cache[n] != 0) {
        return cache[n];
    }

    size_t length;
    if (n % 2 == 0) {
        length = 1 + collatz_length(n / 2, cache);
    } else {
        length = 1 + collatz_length(3 * n + 1, cache);
    }

    if (n < cache.size()) {
        cache[n] = length;
    }

    return length;
}

int main() {
    const size_t MAX_N = 1000000;
    std::vector<size_t> cache(MAX_N, 0);

    size_t max_length = 0;
    unsigned long long int max_start = 1;

    for (unsigned long long int start = 1; start <= 100; ++start) {
        size_t length = collatz_length(start, cache);

        if (length > max_length) {
            max_length = length;
            max_start = start;
        }
    }

    std::cout << "Max length: " << max_length << std::endl;
    std::cout << "Starting value: " << max_start << std::endl;

    return 0;
}