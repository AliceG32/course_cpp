//
// Created by alice on 04.02.2026.
//
#include <iostream>

class Entity_v1 {
private:
    int secretValue;
public:
    explicit Entity_v1(int value) : secretValue(value) {}

    [[nodiscard]] int getValue() const {
        return secretValue;
    }
};

class Entity_v2 {
public:
    int publicValue;
public:
    explicit Entity_v2(int value) : publicValue(value) {}
};

int main() {
    Entity_v1 obj(1);
    std::cout << "Before: " << obj.getValue() << "\n";
    Entity_v1 *objPtr = &obj;
    auto *hackPtr = reinterpret_cast<Entity_v2 *>(objPtr);
    hackPtr->publicValue = 100;
    std::cout << "After first change: " << obj.getValue() << "\n";
    int *secondVar = reinterpret_cast<int *>(objPtr);
    *secondVar = 200;
    std::cout << "After second change: " << obj.getValue() << "\n";
}
