//
// Created by alice on 22.11.2025.
//
#include <iostream>

/////////////////////////////////////////////////////////

class Slow {
public :

    static void test() {
        std::cout << "Slow::test\n";
    }
};

/////////////////////////////////////////////////////////

class Fast {
public :

    static void test() {
        std::cout << "Fast::test\n";
    }
};

/////////////////////////////////////////////////////////

template<typename T>
class Entity : public T {

public:
    void test() const {
        T::test();
    }
};

/////////////////////////////////////////////////////////

int main() {
    Entity<Slow> entity_slow;
    Entity<Fast> entity_fast;

    entity_slow.test();
    entity_fast.test();

}