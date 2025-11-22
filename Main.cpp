//
// Created by alice on 22.11.2025.
//
#include <iostream>
#include <string>

class Entity {
public:
    virtual ~Entity() = default;

    virtual void operation() const = 0;

    [[nodiscard]] virtual std::string getName() const = 0;
};

class BaseEntity : public Entity {
public:
    void operation() const override {
        std::cout << "BaseEntity operation" << std::endl;
    }

    [[nodiscard]] std::string getName() const override {
        return "BaseEntity";
    }
};

template<typename T>
class Decorator : public T {

public:

    void operation() const override {

        std::cout << "Decorator: before operation" << std::endl;
        T::operation();
        std::cout << "Decorator: after operation" << std::endl;
    }

    [[nodiscard]] std::string getName() const override {
        return "Decorated " + T::getName();
    }
};

int main() {
    std::cout << "Entity" << std::endl;
    BaseEntity basic;
    basic.operation();
    std::cout << "Name: " << basic.getName() << std::endl;

    std::cout << "\nDecorated Entity" << std::endl;
    Decorator<BaseEntity> decorated;
    decorated.operation();
    std::cout << "Name: " << decorated.getName() << std::endl;

    return 0;
}