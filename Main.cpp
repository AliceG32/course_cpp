//
// Created by alice on 22.11.2025.
//
#include <iostream>
#include <string>

template<typename T>
class Entity : public T {
public:

    void performOperation() const {
        T::execute();
    }

    [[nodiscard]] std::string getDescription() const {
        return "Entity with " + T::getName();
    }
};

class BaseStrategy {
public:
    static void execute() {
        std::cout << "Base strategy execution" << std::endl;
    }

    static std::string getName() {
        return "BaseStrategy";
    }
};

class BaseStrategy2 {
public:
    static void execute() {
        std::cout << "Base strategy2 execution" << std::endl;
    }

    static std::string getName() {
        return "BaseStrategy2";
    }
};

int main() {
    Entity<BaseStrategy> entity;
    Entity<BaseStrategy2> entity2;

    entity.performOperation();
    std::cout << entity.getDescription() << std::endl;

    entity2.performOperation();
    std::cout << entity2.getDescription() << std::endl;

    return 0;
}