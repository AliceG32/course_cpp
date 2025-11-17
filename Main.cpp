//
// Created by alice on 16.11.2025.
//
#include <string>
#include <utility>
#include <type_traits>

class Person {
private:
    std::string name_;
    int age_;
    int grade_;

public:

    Person(std::string name, int age, int grade)
            : name_(std::move(name)), age_(age), grade_(grade) {}

    [[nodiscard]] const std::string &getName() const { return name_; }

    [[nodiscard]] int getAge() const { return age_; }

    [[nodiscard]] int getGrade() const { return grade_; }
};

class Builder {
private:
    std::string name_;
    int age_;
    int grade_;

public:
    Builder() : name_(""), age_(0), grade_(0) {}

    Builder &name(const std::string &name) {
        name_ = name;
        return *this;
    }

    Builder &age(int age) {
        age_ = age;
        return *this;
    }

    Builder &grade(int grade) {
        grade_ = grade;
        return *this;
    }

    [[nodiscard]] Person get() const {
        return {name_, age_, grade_};
    }
};

int main() {
    auto person = Builder().name("Ivan").age(25).grade(10).get();

    static_assert(std::is_same_v<decltype(person), Person>);

    return 0;
}