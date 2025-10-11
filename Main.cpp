#include <iostream>

class Entity_v1 {
public:
    virtual ~Entity_v1() = default;

    virtual void test() {
        std::cout << "Entity_v1::test()" << std::endl;
    }
};

class Entity_v2 {
public:
    virtual ~Entity_v2() = default;

    virtual void test() {
        std::cout << "Entity_v2::test()" << std::endl;
    }
};

class Adapter_v1 : public Entity_v1 {
public:
    virtual ~Adapter_v1() = default;

    virtual void test_v1() = 0;

    void test() override final {
        test_v1();
    }
};

class Adapter_v2 : public Entity_v2 {
public:
    virtual ~Adapter_v2() = default;

    virtual void test_v2() = 0;

    void test() override final {
        test_v2();
    }
};

class Client : public Adapter_v1, public Adapter_v2 {
public:
    void test_v1() override {
        std::cout << "Client::test_v1() - specialized implementation for Entity_v1" << std::endl;
    }

    void test_v2() override {
        std::cout << "Client::test_v2() - specialized implementation for Entity_v2" << std::endl;
    }
};

int main() {
    Client client;

    Entity_v1 *entity1 = &client;
    Entity_v2 *entity2 = &client;

    std::cout << "Calling through Entity_v1 pointer:" << std::endl;
    entity1->test();

    std::cout << "Calling through Entity_v2 pointer:" << std::endl;
    entity2->test();

    std::cout << "Calling directly through Client:" << std::endl;
    client.test_v1();
    client.test_v2();

    return 0;
}