//
// Created by alice on 22.11.2025.
//
#include <iostream>

////////////////////////////////////////////////////

class Entity {
public:
    virtual ~Entity() = default;

    virtual void test() const = 0;
};

////////////////////////////////////////////////////

class Client : public Entity {
public:
    void test() const override {
        std::cout << "Client::test\n";
    }
};

////////////////////////////////////////////////////

class Server : public Entity {
public:
    void test() const override {
        std::cout << "Server::test\n";
    }
};

////////////////////////////////////////////////////

template<typename T>
class Decorator : public T {
public:
    [[maybe_unused]] void test() const override {
        std::cout << "Decorator::test : ";
        T::test();
    }
};

////////////////////////////////////////////////////

int main() {

    Entity *entity_1 = new Client;
    Entity *entity_2 = new Decorator<Client>;

    entity_1->test();
    entity_2->test();

    delete entity_2;
    delete entity_1;
}