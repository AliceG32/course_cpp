//
// Created by alice on 19.10.2025.
//
////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////

class Vector {
public :

    Vector() : m_array(nullptr), m_size(0) {
        std::cout << "Vector:: Vector (1)\n";
    }

//  --------------------------------------------------------------------------------

    Vector(std::initializer_list<int> list) : Vector() {
        std::cout << "Vector:: Vector (2)\n";

        m_capacity = m_size = std::size(list);
        m_array = (m_size = std::size(list)) ? new int[m_size]{} : nullptr;

        std::ranges::copy(list, m_array);
    }

//  --------------------------------------------------------------------------------

    Vector(Vector const &other) : Vector() {
        std::cout << "Vector:: Vector (3)\n";

        m_capacity = m_size = other.m_size;
        m_array = (m_size = other.m_size) ? new int[m_size]{} : nullptr;

        std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
    }

//  --------------------------------------------------------------------------------

    Vector(Vector &&other)
 noexcept             :
            m_array(std::exchange(other.m_array, nullptr)),
            m_size(std::exchange(other.m_size, 0)),
            m_capacity(std::exchange(other.m_capacity, 0)) {
        std::cout << "Vector:: Vector (4)\n";
    }

//  --------------------------------------------------------------------------------

    ~Vector() {
        std::cout << "Vector::~Vector\n";

        delete[] m_array;
    }

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // error
//	{
//		std::cout << "Vector::operator= (1)\n";
//
//		if (this != &other)
//		{
//			delete[] m_array;
//
//			m_array = (m_size = other.m_size) ? new int[m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // bad
//	{
//		std::cout << "Vector::operator= (2)\n";
//
//		if (this != &other)
//		{
//			auto array = other.m_size ? new int[other.m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, array);
//
//			delete[] std::exchange(m_array, array);
//
//			m_size = other.m_size;
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector && other) // bad
//	{
//		std::cout << "Vector::operator= (3)\n";
//
//		if (this != &other)
//		{
//			delete[] m_array;
//
//			m_array = std::exchange(other.m_array, nullptr);
//
//			m_size  = std::exchange(other.m_size,  0      );
//		}
//
//		return *this;
//	}

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

        int *new_array = new int[new_capacity]{};

        if (m_array != nullptr) {
            std::ranges::copy(m_array, m_array + m_size, new_array);
            delete[] m_array;
        }

        m_array = new_array;
        m_capacity = new_capacity;
    }


    void push_back(int value) {
        if (m_size >= m_capacity) {
            std::size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            reserve(new_capacity);
        }

        m_array[m_size] = value;
        ++m_size;
    }

    void clear() {
        m_size = 0;
    }

    int &operator[](std::size_t index) {
        assert(index < m_size);
        return m_array[index];
    }

    const int &operator[](std::size_t index) const {
        assert(index < m_size);
        return m_array[index];
    }

private :

    int *m_array = nullptr;

    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};

////////////////////////////////////////////////////////////////////////////////////
void test_basic_functionality() {
    Vector v;
    assert(v.empty());
    assert(v.capacity() == 0);
    assert(v.empty() == true);

    v.push_back(10);
    assert(v.size() == 1);
    assert(v.capacity() == 1);
    assert(v[0] == 10);

    v.push_back(20);
    assert(v.size() == 2);
    assert(v.capacity() == 2);
    assert(v[1] == 20);
}

void test_capacity_growth() {
    Vector v;

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
}

void test_clear_and_reuse() {
    Vector v;
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

void test_initializer_list_and_copy() {
    Vector v1 = {1, 2, 3, 4, 5};
    assert(v1.size() == 5);
    assert(v1.capacity() == 5);

    const Vector &v2 = v1;
    assert(v2.size() == 5);
    assert(v2[0] == 1);
    assert(v2[4] == 5);

}

int main() {
    test_basic_functionality();

    test_capacity_growth();

    test_clear_and_reuse();

    test_initializer_list_and_copy();
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////