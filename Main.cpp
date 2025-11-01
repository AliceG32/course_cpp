//
// Created by alice on 31.10.2025.
//
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class Vector {
public:

    Vector() : m_array(nullptr), m_size(0), m_capacity(0) {
        std::cout << "Vector::Vector (1)\n";
    }

//  --------------------------------------------------------------------------------

    Vector(std::initializer_list<T> list) : Vector() {
        std::cout << "Vector::Vector (2)\n";

        m_capacity = m_size = std::size(list);
        m_array = (m_size > 0) ? new T[m_size]{} : nullptr;

        std::ranges::copy(list, m_array);
    }

//  --------------------------------------------------------------------------------

    Vector(Vector const &other) : Vector() {
        std::cout << "Vector::Vector (3)\n";

        m_capacity = m_size = other.m_size;
        m_array = (m_size > 0) ? new T[m_size]{} : nullptr;

        std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
    }

//  --------------------------------------------------------------------------------

    Vector(Vector &&other) noexcept:
            m_array(std::exchange(other.m_array, nullptr)),
            m_size(std::exchange(other.m_size, 0)),
            m_capacity(std::exchange(other.m_capacity, 0)) {
        std::cout << "Vector::Vector (4)\n";
    }

//  --------------------------------------------------------------------------------

    ~Vector() {
        std::cout << "Vector::~Vector\n";

        delete[] m_array;
    }

//  --------------------------------------------------------------------------------

    auto &operator=(Vector other) {
        std::cout << "Vector::operator= (4)\n";

        swap(other);

        return *this;
    }

//  --------------------------------------------------------------------------------

    void swap(Vector &other) {
        std::swap(m_array, other.m_array);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    [[nodiscard]] std::size_t capacity() const {
        return m_capacity;
    }

    [[nodiscard]] std::size_t size() const {
        return m_size;
    }

    [[nodiscard]] bool empty() const {
        return m_size == 0;
    }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= m_capacity)
            return;

        T *new_array = new T[new_capacity]{};

        if (m_array != nullptr) {
            std::ranges::copy(m_array, m_array + m_size, new_array);
            delete[] m_array;
        }

        m_array = new_array;
        m_capacity = new_capacity;
    }

    void push_back(T &&value) {
        if (m_size >= m_capacity) {
            std::size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            reserve(new_capacity);
        }

        m_array[m_size] = std::move(value);
        ++m_size;
    }

    void clear() {
        m_size = 0;
    }

    T &operator[](std::size_t index) {
        assert(index < m_size);
        return m_array[index];
    }

    const T &operator[](std::size_t index) const {
        assert(index < m_size);
        return m_array[index];
    }

private:

    T *m_array = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};

////////////////////////////////////////////////////////////////////////////////////

void test_clear_and_reuse() {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::size_t old_capacity = v.capacity();
    v.clear();

    assert(v.empty());
    assert(v.capacity() == old_capacity);
    assert(v.empty() == true);

    v.push_back(100);
    assert(v.size() == 1);
    assert(v[0] == 100);
}


int main() {

    Vector<double> v_double;
    v_double.push_back(3.14);
    v_double.push_back(2.71);
    assert(v_double.size() == 2);
    assert(std::abs(v_double[0] - 3.14) < 1e-10);
    assert(std::abs(v_double[1] - 2.71) < 1e-10);

    Vector<std::string> v_string;
    v_string.push_back("Hello");
    v_string.push_back("World");
    assert(v_string.size() == 2);
    assert(v_string[0] == "Hello");
    assert(v_string[1] == "World");

    Vector<int> v1 = {1, 2, 3, 4, 5};
    assert(v1.size() == 5);
    assert(v1.capacity() == 5);

    Vector<int> v2 = v1;

    assert(v2.size() == 5);

    Vector<int> v;
    v.push_back(1);
    assert(v.capacity() == 1);
    v.push_back(2);
    assert(v.capacity() == 2);
    v.push_back(3);
    assert(v.capacity() == 4);
    v.push_back(4);
    assert(v.capacity() == 4);
    v.push_back(5);
    assert(v.capacity() == 8);

    test_clear_and_reuse();

    Vector<int> source = {1, 2, 3, 4, 5};
    Vector<int> target = {10, 20};

    target = source;

    assert(target.size() == 5);

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////