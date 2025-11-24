//
// Created by alice on 22.11.2025.
//
#include <iostream>
#include <memory>
#include <vector>

class State {
public:
    virtual ~State() = default;

    virtual void execute() = 0;
};

class Peaceful : public State {
public:
    void execute() override { std::cout << "Peaceful behavior\n"; }
};

class Aggressive : public State {
public:
    void execute() override { std::cout << "Aggressive behavior\n"; }
};

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void action() = 0;

    void setState(std::unique_ptr<State> s) { state = std::move(s); }

protected:
    std::unique_ptr<State> state;
};

class UnitGroup : public GameObject {
    std::vector<std::shared_ptr<GameObject>> units;
public:
    void add(const std::shared_ptr<GameObject>& unit) { units.push_back(unit); }

    void action() override {
        for (auto &unit: units) unit->action();
    }
};

class Man : public GameObject {
public:
    void action() override {
        std::cout << "Man: ";
        state->execute();
    }
};

class Tank : public GameObject {
public:
    void action() override {
        std::cout << "Tank: ";
        state->execute();
    }
};

class Factory {
public:
    virtual std::shared_ptr<GameObject> create() = 0;
};

class ManFactory : public Factory {
public:
    std::shared_ptr<GameObject> create() override {
        return std::make_shared<Man>();
    }
};

class TankFactory : public Factory {
public:
    std::shared_ptr<GameObject> create() override {
        return std::make_shared<Tank>();
    }
};

int main() {

    ManFactory manFactory;
    TankFactory tankFactory;

    auto man = manFactory.create();
    auto tank = tankFactory.create();

    man->setState(std::make_unique<Peaceful>());
    tank->setState(std::make_unique<Aggressive>());

    auto team = std::make_shared<UnitGroup>();
    team->add(man);
    team->add(tank);

    man->action();
    tank->action();
    team->action();

    return 0;
}