//
// Created by alice on 30.09.2025.
//
#include <iostream>
#include <cassert>

class Entity;

class HealthTesterAttorney {
private:
    static int getHealth(const Entity &entity);

    static void setHealth(Entity &entity, int health);

    friend class HealthTester;
};

class DamageTesterAttorney {
private:
    static int calculateDamage(const Entity &entity, int baseDamage);

    friend class DamageTester;
};

class Entity {
private:
    int health = 100;
    int defense = 10;

    [[nodiscard]] int getHealth() const {
        return health;
    }

    void setHealth(int health1) {
        health = health1;
    }

    [[nodiscard]] int calculateDamage(int baseDamage) const {
        return std::max(0, baseDamage - defense);
    }

    friend class HealthTesterAttorney;

    friend class DamageTesterAttorney;

public:

    void takeDamage(int damage) {
        health -= calculateDamage(damage);
        if (health < 0) health = 0;
    }

    [[nodiscard]] bool isAlive() const {
        return health > 0;
    }
};

int HealthTesterAttorney::getHealth(const Entity &entity) {
    return entity.getHealth();
}

void HealthTesterAttorney::setHealth(Entity &entity, int health) {
    entity.setHealth(health);
}

int DamageTesterAttorney::calculateDamage(const Entity &entity, int baseDamage) {
    return entity.calculateDamage(baseDamage);
}

class HealthTester {
public:
    static void testGetSetHealth() {
        Entity entity;

        assert(HealthTesterAttorney::getHealth(entity) == 100);

        HealthTesterAttorney::setHealth(entity, 75);
        assert(HealthTesterAttorney::getHealth(entity) == 75);

        HealthTesterAttorney::setHealth(entity, 0);
        assert(HealthTesterAttorney::getHealth(entity) == 0);

        std::cout << "HealthTester: все тесты пройдены!\n";
    }
};

class DamageTester {
public:
    static void testCalculateDamage() {
        Entity entity;

        assert(DamageTesterAttorney::calculateDamage(entity, 20) == 10);

        assert(DamageTesterAttorney::calculateDamage(entity, 5) == 0);

        assert(DamageTesterAttorney::calculateDamage(entity, -5) == 0);

        std::cout << "DamageTester: все тесты пройдены!\n";
    }
};

class TestSystem {
public:
    static void runAllTests() {

        HealthTester::testGetSetHealth();
        DamageTester::testCalculateDamage();

        std::cout << "Все тесты успешно завершены!\n";
    }
};

int main() {
    TestSystem::runAllTests();

    Entity player;
    player.takeDamage(15);
    if (player.isAlive()) {
        std::cout << "Player is alive" << "\n";
    } else {
        std::cout << "Player is not alive";
    }

    return 0;
}