//
// Created by alice on 15.11.2025.
//
#include <type_traits>

struct true_type {
    static constexpr bool value = true;
};

struct false_type {
    static constexpr bool value = false;
};

template<typename T>
struct remove_const {
    using type = T;
};
template<typename T>
struct remove_const<const T> {
    using type = T;
};
template<typename T>
struct remove_const<const volatile T> {
    using type = volatile T;
};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

template<bool B, typename T, typename F>
struct conditional {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template<typename T>
true_type test_is_class(int T::*);

template<typename T>
false_type test_is_class(...);

template<typename T>
struct is_class : decltype(test_is_class<T>(nullptr)) {
};

template<typename T>
inline constexpr bool is_class_v = is_class<T>::value;

template<typename T>
struct add_const {
    using type = const T;
};

template<typename T>
struct add_const<const T> {
    using type = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct decay {
private:
    using U = std::remove_reference_t<T>;
public:
    using type = conditional_t<
            std::is_array_v<U>,
            std::remove_extent_t<U>*,
            conditional_t<
                    std::is_function_v<U>,
                    U*,
                    remove_const_t<U>
            >
    >;
};

template<typename T>
using decay_t = typename decay<T>::type;

class TestClass {
};

struct TestStruct {
};

static_assert(is_class_v<TestClass>, "TestClass should be a class");
static_assert(is_class_v<TestStruct>, "TestStruct should be a class");
static_assert(!is_class_v<int>, "int should not be a class");

static_assert(std::is_same_v<add_const_t<int>, const int>, "add_const_t<int> should be const int");
static_assert(std::is_same_v<add_const_t<const int>, const int>, "add_const_t<const int> should be const int");

static_assert(std::is_same_v<remove_const_t<const int>, int>, "remove_const_t<const int> should be int");
static_assert(std::is_same_v<remove_const_t<int>, int>, "remove_const_t<int> should be int");

static_assert(std::is_same_v<decay_t<int>, int>, "decay_t<int> should be int");
static_assert(std::is_same_v<decay_t<const int>, int>, "decay_t<const int> should be int");
static_assert(std::is_same_v<decay_t<int&>, int>, "decay_t<int&> should be int");
static_assert(std::is_same_v<decay_t<int&&>, int>, "decay_t<int&&> should be int");
static_assert(std::is_same_v<decay_t<int[5]>, int*>, "decay_t<int[5]> should be int*");

static_assert(std::is_same_v<conditional_t<true, int, double>, int>, "conditional_t<true, int, double> should be int");
static_assert(std::is_same_v<conditional_t<false, int, double>, double>, "conditional_t<false, int, double> should be double");

int main() {
    return 0;
}